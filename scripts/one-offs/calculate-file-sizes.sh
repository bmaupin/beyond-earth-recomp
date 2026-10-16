#!/usr/bin/env bash
set -euo pipefail

binary=private/beyond-earth/libCvGameCoreDLL_Expansion1.so
tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

# Extract function addresses, sizes and names.
readelf -Ws "$binary" |
    awk '$4 == "FUNC" && $3 > 0 {
        print "0x"$2 "\t"$3 "\t"$8
    }' |
    sort -u > "$tmpdir/functions.tsv"

# Map function start addresses to source locations.
cut -f1 "$tmpdir/functions.tsv" |
    addr2line -f -C -e "$binary" |
    awk 'NR % 2 == 0' > "$tmpdir/locations.txt"

# Combine symbol information with source locations and aggregate.
paste "$tmpdir/functions.tsv" "$tmpdir/locations.txt" |
    awk -F '\t' '
        {
            path = $4
            sub(/:[0-9]+$/, "", path)

            if (path == "??" || path == "??:0" || path !~ /\//)
                next

            bytes[path] += $2
            count[path]++
        }
        END {
            for (path in bytes)
                printf "%10d %5d %s\n", bytes[path], count[path], path
        }
    ' |
    egrep -v "clang\+llvm|MSVC/|Public/External" |
    awk '{print "| " $3 " | " $1 " |  |"}' |
    sort -u