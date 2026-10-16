#!/usr/bin/env bash

# Compare an object file against the Beyond Earth game core binary. This is used to
# validate that the source code matches the binary. e.g.

civbe_gamecore=private/beyond-earth/libCvGameCoreDLL_Expansion1.so

if [ -z "${1}" ]; then
    echo "Error: Provide an object file to compare, for example:" >&2
    echo "    ${0} private/build/CvGameCoreEnumSerialization.o" >&2
    exit 1
fi
object_file="${1}"

total_current_score=0
total_max_score=0

compare_functions() {
    source_binary="${1}"
    target_binary="${2}"
    function_name="${3}"

    tmp_asm_file=/tmp/libCvGameCoreDLL_Expansion1.so.asm

    # "grep -F" matches the string as a literal string (function names can contain asterisks)
    # ":" matches the function declaration
    # "@plt"
    function_name_matches=$(objdump -d --demangle "${source_binary}" | grep -F "${function_name}" | grep ">:" | egrep -v "@plt")

    if [[ "$function_name_matches" = *$'\n'* ]]; then
        echo "Error: More than one match found in the object file" >&2
        echo "${function_name_matches}" >&2
        exit 1
    fi

    function_start_address=$(echo ${function_name_matches} | awk '{print $1}')

    if [ -z "${function_start_address}" ]; then
        echo "Error: Function not found in object file: ${function_name}" >&2
        exit 1
    fi

    # Gets all addresses from the binary and then returns the address of the next function
    function_stop_address=$(objdump -d --demangle "${source_binary}" |
        awk -v start="$function_start_address" '
            /^[[:xdigit:]]+ <.*>:/ && !/@plt/ {
                address = $1
                sub(/:$/, "", address)

                if (found) {
                    print address
                    exit
                }

                if (tolower(address) == tolower(start)) {
                    found = 1
                }
            }
        ')

    # Get the Beyond Earth mangled function name, needed by asm-differ
    civbe_function_start_address=$(nm --defined-only "${target_binary}" |
        # -F allows for function names that contain asterisks
        c++filt | grep -F "${function_name}" |
        egrep -v "::ms_nestingOffset" |
        uniq |
        awk '{print $1}');

    if [[ "$civbe_function_start_address" = *$'\n'* ]]; then
        echo "Error: More than one match found in the Beyond Earth game core for function ${function_name}" >&2
        echo "$civbe_function_start_address" >&2
        exit 1
    fi

    mangled_function_name=$(
        nm --defined-only "${target_binary}" |
        grep "^$civbe_function_start_address " |
        # Sometimes it can return multiple mangled function names that resolve to the same address
        head -n 1 |
        awk '{print $3}'
    )

    if [ -z "${mangled_function_name}" ]; then
        echo "Error: Mangled function name not found" >&2
        echo "    function_name: ${function_name}" >&2
        echo "    target_binary: ${target_binary}" >&2
        exit 1
    fi

    # Uncomment for debugging
    # echo $function_name
    # echo $mangled_function_name
    # echo $function_start_address
    # echo $function_stop_address
    # echo private/tools/asmdiffer/bin/asm-differ -o \--file "${source_binary}" \--ref-file "${target_binary}" \--base-asm "${tmp_asm_file}" \--no-pager \--stop-at-ret "${mangled_function_name}"
    # exit 1

    # Write just that function to an assembly file; asm-differ can't compare object files directly to .so files
    objdump --no-show-raw-insn -m i386 -d -rz -j .text --disassemble="${mangled_function_name}" \
        --line-numbers "${target_binary}" |
        tail -n +7 > "${tmp_asm_file}"

    # Unfortunately asm-differ's object file comparison cannot properly detect the end of
    # a function from an .asm text file, so we calculate the number of lines to compare
    # and use --max-lines
    object_num_lines=$(objdump --no-show-raw-insn -m i386 -d -z -j .text --disassemble="${mangled_function_name}" \
        "${source_binary}" | grep -E '^[[:space:]]*[[:xdigit:]]+:' | wc -l)
    game_core_num_lines=$(objdump --no-show-raw-insn -m i386 -d -z -j .text --disassemble="${mangled_function_name}" \
        "${target_binary}" | grep -E '^[[:space:]]*[[:xdigit:]]+:' | wc -l)

    if [[ $game_core_num_lines -gt $object_num_lines ]]; then
        max_lines=$game_core_num_lines
    else
        max_lines=$object_num_lines
    fi

    raw_score=$(private/tools/asmdiffer/bin/asm-differ --format json -o --file "${source_binary}" --ref-file "${target_binary}" --base-asm "${tmp_asm_file}" --no-pager --max-lines "${max_lines}" "${mangled_function_name}" |
        jq | grep score
    )
    current_score=$(echo "${raw_score}" | grep current_score | awk '{print $2}' | sed 's/[^0-9]*//g')
    # The last function in the file doesn't need the adjustment as the file ends so
    # asm-differ calculates the score correctly
    if [[ "${function_name}" != "${last_function_in_file}" && "$current_score" -ge 100 ]]; then
        # Using --max-lines automatically increases current_score by 100, so adjust
        current_score=$((current_score - 100))
    fi
    max_score=$(echo "${raw_score}" | grep max_score | awk '{print $2}' | sed 's/[^0-9]*//g')
    total_current_score=$((total_current_score+$current_score))
    total_max_score=$((total_max_score+$max_score))

    # A score of zero means an identical match
    score=$(((max_score - current_score) * 100 / max_score))

    echo "${function_name}: ${score}%"
    # NOTE: Scores under 0 can result if source function has more instructions than source
    if [[ "$score" -lt 95 || "$score" -gt 100 ]]; then
        echo "    objdump --no-show-raw-insn -m i386 -d -rz -j .text --disassemble=${mangled_function_name} --line-numbers ${target_binary} | tail -n +7 > ${tmp_asm_file}; private/tools/asmdiffer/bin/asm-differ" -o \--file "${source_binary}" \--ref-file "${target_binary}" \--base-asm "${tmp_asm_file}" \--no-pager \--max-lines "${max_lines}" "${mangled_function_name}"
    fi
}

source_file="$(basename ${object_file} .o).cpp"
# Get the list of functions from the Beyond Earth game core, in case we missed any
mapfile -t functions < <( nm --defined-only "${civbe_gamecore}" |
    awk '$2 ~ /^[Tt]$/ { print "0x" $1 }' |
    addr2line -f -C -e "${civbe_gamecore}" |
    awk -v source_file="$source_file" 'NR % 2 { name = $0; next } index($0, source_file) { print name }' |
    uniq )

last_function_in_file=$(nm --defined-only --demangle private/build/CvDllCity.o | grep T | sort | tail -n 1 | awk '{ $1 = ""; $2 = ""; sub(/^  */, ""); print }')

for function in "${functions[@]}"; do
    compare_functions "${object_file}" "${civbe_gamecore}" "${function}"
done

total_score=$(((total_max_score - total_current_score) * 100 / total_max_score))

echo
echo "${object_file}: ${total_score}%"