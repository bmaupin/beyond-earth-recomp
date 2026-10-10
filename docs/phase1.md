# Phase 1: Reconstruct source with limited changes

## Goal

The goal of this phase is to reconstruct as much of the Beyond Earth game core source from the Civ 5 game source where possible while only introducing limited changes.

- The primary goal is the compiled source code should result in machine code that matches the Beyond Earth game core binary after normalising relocation-dependent addresses and symbol references
  - Normalisation must preserve referenced targets and must not hide differences in instructions, control flow, constants, or field offsets
  - Because we are compiling individual units of the game core source separately, identical byte-for-byte machine code is not a goal in this phase
- A secondary goal is that the source code should match the Civ 5 source code as much as possible

"Matching" in this document refers to code that meets the goals for this phase as described in this section.

TODO: Add examples of differences in the disassembly that would still be considered a match

## Steps

1. For each source file, get a list of function names from the Beyond Earth game core binary, e.g.

   ```
   nm --defined-only private/beyond-earth/libCvGameCoreDLL_Expansion1.so |
     awk '$2 ~ /^[Tt]$/ { print "0x" $1 }' |
     addr2line -f -C -e private/beyond-earth/libCvGameCoreDLL_Expansion1.so |
     awk 'NR % 2 { name = $0; next } /\/CvProjectProductionAI\.cpp:/ { print name }' |
     sort -u
   ```

   Compare this list against Civ 5 source to determine which functions are in both game cores and which are only in one game core

1. Determine the next function to recompile
   1. Look at the file timestamps in [`src/`](../../src/) and the commit history to determine the most recent file and function that was recompiled

   1. Open that file in the Civ 5 game core source to determine if all functions in that file have been recompiled. If not, pick the next function in that file.

   1. If all functions in that file have been recompiled pick the next file from the list under _Implementation files_ in [todo.md](../todo.md); do not pick previous files, even if they are unchecked in the list

1. See if that function is in the Beyond Earth game core, e.g.

   ```
   $ objdump -d --demangle private/beyond-earth/libCvGameCoreDLL_Expansion1.so | grep 'FDataStream.*YieldTypes'
   0045b39c <operator<<(FDataStream&, YieldTypes const&)>:
   ```

1. If the function or any supporting constructs do not exist in the Beyond Earth game core, copy just the declaration, comment it out, and add a note, e.g.

   ```c++
   // NOTE: getWorldSizeMaxConscript does not exist in Beyond Earth game core
   // int getWorldSizeMaxConscript(const CvPolicyEntry& kPolicy);
   ```

1. If the function exists in Beyond Earth and Civ 5
   1. Disassemble the Civ 5 game core and find that function

   1. Disassemble the Beyond Earth game core and find that function

   1. Compare the functions to determine if they already match with no additional changes needed

   1. If the functions do not match, check a different Civ 5 game core to see if there's a matching function (Civ 5 has 3 different game cores all with source)
      - If a match is found, do not compare it to other Civ 5 game cores, only use the matching game core

   1. If the functions match, copy the function from the Civ 5 game core source to an identically named file in [`src/`](../../src/)

1. If the functions do not match, or the functions only exist in Beyond Earth and not Civ 5
   1. If the changed or new regions for a function contain more than 100 machine instructions in total that need to be implemented (excluding alignment padding), do not implement the function but add a TODO with the function name and number of new or changed instructions, e.g.

      ```c++
      // TODO: CvPlayerManager::RefreshDangerPlots() (127 changed instructions)
      ```

      Then skip the steps below and instead move to the next function

   1. Otherwise, implement the function and add a comment indicating an overview of the differences, e.g. if the difference is in the function:

      ```c++
      // Beyond Earth's replay format starts at version 1; Civ 5 returns 2.
      return 1;
      ```

      Or if the function only exists in Beyond Earth:

      ```c++
      // Beyond Earth exposes mid- and late-game turns instead of barbarian scaling.
      int CvDllGameSpeedInfo::GetMidGameTurn()
      {
      ```

      - Decompiled code from Ghidra may be helpful in reconstructing missing source code
      - Do not write unit tests; the source code will be compiled and compared to the Beyond Earth game core binary

1. Also copy any necessary supporting structures from the Civ 5 game core source `.h` files into matching files in [`src/`](../../src/)
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

1. If the disassembly does not match, repeat the steps above until it matches

1. Continue to the next function in the source file

1. Once modifications are done, mark all all modified `.cpp` and `.h` files as checked in [docs/todo.md](../todo.md) only if the resulting disassembly matches
   - This should be the case for all files except for files where there are functions that are not yet implemented

1. Update the Progress in [docs/todo.md](../todo.md)
   1. Calculate the number of recompiled functions

      ```
      find src -type f -name '*.cpp' -print |
        ctags --quiet \
          --languages=C++ \
          --kinds-C++=f \
          -f - \
          -L - |
        awk -F '\t' '$4 == "f" { count++ } END { print count + 0 }'
      ```

   1. Update the text under the badge, e.g.

      ```
      25 functions recompiled out of ~ 14453
      ```

   1. Calculate the percentage, e.g.

      25/14453\*100

   1. Update the badge, e.g.

      ```
      [![Progress](https://img.shields.io/badge/progress-0.2%25-red)](../src/)
      ```

      (`%25` is URL-encoded `%`)
      - Once progress is > 1%, only show whole numbers
      - Once progress is > 10%, change the colour to orange and move the badge to README.md in the root of the repository
      - Once progress is > 50%, change the colour to yellow
      - Once progress is > 99%, change the colour to green

   1. Update the number of total functions recompiled
      - Increment for every function that exists in Beyond Earth but not in Civ 5
      - Decrement for every function that exists in Civ 5 but not in Beyond Earth

1. If an AI agent is performing these steps, provide a minimal summary at the end or a document in `docs/ai` containing:
   - A table with a row for the `.cpp` file as well as its corresponding `.h` file with these columns:
     - The name of the file
     - Whether that file was copied without changes from Civ 5 or if it needed modifications
     - If the file has any remaining functions that need to be implemented
     - How long it took to implement the file
   - A table for each file with remaining functions that need to be implemented with these columns:
     - The name of the file
     - The name of the function
     - How many instructions the function has including how many changed/new
   - If a file is created, provide a link
