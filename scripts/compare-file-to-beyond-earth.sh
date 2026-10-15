#!/usr/bin/env bash

# Compare an object file against the Beyond Earth game core binary. This is used to
# validate that the source code matches the binary. e.g.

civbe_gamecore=private/beyond-earth/libCvGameCoreDLL_Expansion1.so

if [ -z "${1}" ]; then
    echo "Error: Provide an object file to compare, for example:" >&2
    echo "    ${0} private/build/CvGameCoreEnumSerialization.o" >&2
    exit 1
fi
file_name="${1}"

compare_functions() {
    source_binary="${1}"
    target_binary="${2}"
    function_name="${3}"

    # "grep -F" matches the string as a literal string (function names can contain asterisks)
    # ":" matches the function declaration
    # "@plt"
    function_name_matches=$(objdump -d --demangle "${source_binary}" | grep -F "${function_name}" | grep ">:" | egrep -v "@plt")

    if [[ "$function_name_matches" = *$'\n'* ]]; then
        echo "Error: More than one match found in the Civ 5 game core" >&2
        echo "${function_name_matches}" >&2
        exit 1
    fi

    function_start_address=$(echo ${function_name_matches} | awk '{print $1}')

    # If the function isn't in the Civ 5 binary, skip silently
    if [ -z "${function_start_address}" ]; then
        echo "Function not found in Civ 5 game cores: ${function_name}"
        return 1
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
        uniq |
        awk '{print $1}');

    if [[ "$civbe_function_start_address" = *$'\n'* ]]; then
        echo "Error: More than one match found in the Beyond Earth game core" >&2
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
    # echo $mangled_function_name
    # echo $function_start_address
    # echo $function_stop_address
    # echo private/tools/asmdiffer/bin/asm-differ \-e "${mangled_function_name}" 0 \--write-asm /tmp/libCvGameCoreDLL_Expansion1.so.asm
    # echo private/tools/asmdiffer/bin/asm-differ -o \--file "${source_binary}" \--ref-file "${target_binary}" \--base-asm /tmp/libCvGameCoreDLL_Expansion1.so.asm \--no-pager \--stop-at-ret "${mangled_function_name}"
    # exit 1

    # Write just that function to an assembly file; asm-differ can't compare object files directly to .so files
    objdump --no-show-raw-insn -m i386 -d -rz -j .text --disassemble="${mangled_function_name}" \
        --line-numbers "${target_binary}" |
        tail -n +7 > /tmp/libCvGameCoreDLL_Expansion1.so.asm

    score=$(private/tools/asmdiffer/bin/asm-differ --format json -o --file "${source_binary}" --ref-file "${target_binary}" --base-asm /tmp/libCvGameCoreDLL_Expansion1.so.asm --no-pager --stop-at-ret "${mangled_function_name}" |
        jq '((.max_score - .current_score) / .max_score * 100) | round * 100 / 100'
        # jq '{current_score}' |
        # A score of zero means an identical match, although this is rare
        # grep '"current_score": 0' >/dev/null
    )

    echo "${function_name}: ${score}% (${source_binary})"
    # TODO: how can this be fixed?
    if [[ "$score" -lt 0 ]]; then
        echo private/tools/asmdiffer/bin/asm-differ -o \--file "${source_binary}" \--ref-file "${target_binary}" \--base-asm /tmp/libCvGameCoreDLL_Expansion1.so.asm \--no-pager \--stop-at-ret "${mangled_function_name}"
        exit 1
    fi
}

# Store the result of the command in an array
# - 'T': Filter out global function symbols
# - 't': local text symbols, but filter out if they start with '.L', e.g. '.LBB2_2'
mapfile -t functions < <( nm --defined-only --demangle "${file_name}" |
    awk '($2 == "T" || $2 == "t") && $3 !~ /^\.L/ { $1 = ""; $2 = ""; sub(/^  */, ""); print }' |
    uniq )

for function in "${functions[@]}"; do
    compare_functions "${file_name}" "${civbe_gamecore}" "${function}"
done
