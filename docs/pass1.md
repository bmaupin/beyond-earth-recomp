# Pass 1: Copy identical source from Civ 5

## Goal

The goal of this pass is to copy code from the Civ 5 game core source that results in matching machine code in the Beyond Earth game core binary.

- The source code must match without any modifications
- The machine code must match after normalising relocation-dependent addresses and symbol references
- Normalisation must preserve referenced targets and must not hide differences in instructions, control flow, constants, or field offsets

"Matching" in this document refers to code that meets the goals for this pass as described in this section.

TODO: Add examples of differences in the disassembly that would still be considered a match

#### Non-goals

- Identical byte-for-byte machine code is not a goal in this pass
- Implementing source code for functions which do not result in matching machine code in the Beyond Earth game core binary is not a goal in this passs

## Steps

#### Identify functions in Beyond Earth game core

For a particular source file:

1. Get a list of function names from the Beyond Earth game core binary, e.g.

   ```
   nm --defined-only private/beyond-earth/libCvGameCoreDLL_Expansion1.so |
     awk '$2 ~ /^[Tt]$/ { print "0x" $1 }' |
     addr2line -f -C -e private/beyond-earth/libCvGameCoreDLL_Expansion1.so |
     awk 'NR % 2 { name = $0; next } /\/CvProjectProductionAI\.cpp:/ { print name }' |
     sort -u
   ```

1. Compare this list against Civ 5 source to determine which functions are in both game cores and which are only in one game core

#### Process each function

For each function:

1. If the function or any supporting constructs do not exist in the Beyond Earth game core, copy just the declaration, comment it out, and add a note, e.g.

   ```c++
   // NOTE: getWorldSizeMaxConscript does not exist in Beyond Earth game core
   // void CvAliens::Init()
   ```

   Then skip the remaining steps and continue to the next function

1. If the function only exists in the Beyond Earth game core and not Civ 5, add a TODO with the declaration and number of total instructions:

   ```c++
   // TODO: CvAliens::Init() (25 total instructions)
   ```

   Then skip the remaining steps and continue to the next function

1. If the function exists in Beyond Earth and Civ 5
   1. Disassemble the Civ 5 game core and find that function

   1. Disassemble the Beyond Earth game core and find that function

   1. Compare the functions in the machine code to determine if they already match with no additional changes needed

   1. If the functions do not match, check a different Civ 5 game core to see if there's a matching function (Civ 5 has 3 different game cores all with source)
      - If a match is found, do not compare it to other Civ 5 game cores, only use the matching game core

   1. If the functions match, copy the function from the Civ 5 game core source to an identically named file in [`src/`](../src/)

1. If the functions do not match, add a TODO with the declaration and number of total instructions and different instructions:

   ```c++
   // TODO: CvPlayerManager::RefreshDangerPlots() (137 total instructions, 101 differ)
   ```

   Then skip the steps below and instead move to the next function

1. Also copy any necessary supporting structures from the Civ 5 game core source `.h` files into matching files in [`src/`](../src/)
   - Keep the source as close as possible to the Civ 5 game core; use the same file layout, include headers, comments, etc.
   - Take `CvInternalGameCoreUtils.cpp` as an example:
     1. `CvInternalGameCoreUtils.h` should be copied to `src/`
     1. Because it references `CvBuildingClassInfo`, as needed:
        1. `src/CvInfos.h` should be updated to include the definition for `CvBuildingClassInfo`
        1. `src/CvGameCoreDLLPCH.h` should be updated to include `CvInfos.h`
        1. `src/CvGlobals.h` should be updated to include references for `CvBuildingClassInfo`
   - Do not add extra imports that were not in the source files
   - Do not fabricate ABI layout using padding, placeholder members, raw byte offsets, or hardcoded object/array strides—even when verified against the binary
     - If the required layout is incomplete, leave the accessor declared with a specific TODO. Do not substitute an ABI shortcut

1. Compile the source, e.g.

   ```
   docker run --rm \
     -v "$PWD:/work" \
     -w /work \
     civ-recompile \
     /clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04/bin/clang++ \
     -m32 -Os -fPIC -fno-exceptions \
     -isystem /clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04/include/c++/v1 \
     -Isrc \
     -Isrc/Fireworks \
     -c src/CvGameCoreEnumSerialization.cpp \
     -o private/build/CvGameCoreEnumSerialization.o
   ```

1. Disassemble the compiled source and compare the relevant section of the Beyond Earth game core to confirm it matches according to the goal listed above

1. If the disassembly does not match, replace the function with a TODO as described above

1. Continue to the next function in the source file

#### Update the total number of functions in todo.md

1. Once the above steps have been completed

1. Look for a line in [todo.md](todo.md)like this:

   > 1089 functions recompiled out of ~ 14500

   In this example, 14500 is the total number of functions

1. For every function in the file that exists in Beyond Earth but not in Civ 5, increment the number of total functions

1. For every function in the file that exists in Civ 5 but not in Beyond Earth, decrement the number of total functions

1. Do not make other modifications to docs/todo.md
