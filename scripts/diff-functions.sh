#!/usr/bin/env bash

if [ -z "${1}" ]; then
    echo "Error: Provide a function to compare" >&2
    exit 1
fi

function_name="${1}"
civbe_gamecore=private/beyond-earth/libCvGameCoreDLL_Expansion1.so
civ5_gamecore=private/civ5/libCvGameCoreDLL.so
civ5_exp1_gamecore=private/civ5/libCvGameCoreDLL_Expansion1.so
civ5_exp2_gamecore=private/civ5/libCvGameCoreDLL_Expansion2.so

# TODO
# function_name=CvDllMinorCivInfo::CvDllMinorCivInfo
binary=$civ5_gamecore

# ":" matches the function declaration
# "@plt"
function_name_matches=$(objdump -d --demangle "${binary}" | grep "${function_name}.*:" | egrep -v "@plt")


if [[ "$function_name_matches" = *$'\n'* ]]; then
    echo "Error: More than one match found" >&2
    exit 1
fi

function_start_address=$(echo ${function_name_matches} | awk '{print $1}')

# Gets all addresses from the binary and then returns the
function_stop_address=$(objdump -d --demangle "${binary}" |
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
civbe_function_start_address=$(nm --defined-only "${civbe_gamecore}" |
    c++filt | grep "${function_name}" |
    uniq |
    awk '{print $1}');

if [[ "$civbe_function_start_address" = *$'\n'* ]]; then
    echo "Error: More than one match found" >&2
    echo "$civbe_function_start_address"
    exit 1
fi

mangled_function_name=$(
    nm --defined-only "${civbe_gamecore}" |
    grep "^$civbe_function_start_address " |
    # Sometimes it can return multiple mangled function names that resolve to the same address
    head -n 1 |
    awk '{print $3}'
)

# echo $function_start_address
# echo $function_stop_address
# echo $mangled_function_name

private/tools/asmdiffer/bin/asm-differ --no-pager -e "${mangled_function_name}" "0x${function_start_address}" "0x${function_stop_address}"
