# Recompile matching functions

ⓘ These steps are for recompiling functions which exist in both the Beyond Earth game core and the Civ 5 game core

1. Determine the next function to recompile
   1. Look at the file timestamps in [`src/`](../../src/) and the commit history to determine the most recent file and function that was recompiled

   1. Open that file in the Civ 5 game core source to determine if all functions in that file have been recompiled. If not, pick the next function in that file.

   1. If all functions in that file have been recompiled pick the next file from the list under _Implementation files_ in [todo.md](../todo.md); do not pick previous files, even if they are unchecked in the list

1. See if that function is in the Beyond Earth game core, e.g.

   ```
   $ objdump -d --demangle private/beyond-earth/libCvGameCoreDLL_Expansion1.so | grep 'FDataStream.*YieldTypes'
   0045b39c <operator<<(FDataStream&, YieldTypes const&)>:
   ```

1. Disassemble the Civ 5 game core and find that function

1. Disassemble the Beyond Earth game core and find that function

1. Compare the functions to determine if they are identical at a source level

   TODO: What are some differences in the disassembly that do not indicate that the source is different?

1. If the functions are not source-level identical, check a different Civ 5 game core to see if there's a matching function (Civ 5 has 3 different game cores all with source)

1. If a matching function is still not found, continue to the next function

1. If the functions are identical, copy the function from the Civ 5 game core source to an identically named file in [`src/`](../../src/)

1. Also copy any necessary supporting structures from the Civ 5 game core source `.h` files into matching files in [`src/`](../../src/)
   - Keep the source as close as possible to the Civ 5 game core; include headers, comments, etc.
   - Take `CvInternalGameCoreUtils.cpp` as an example:
     1. `CvInternalGameCoreUtils.h` should be copied to `src/`
     1. Because it references `CvBuildingClassInfo`, as needed:
        1. `src/CvInfos.h` should be updated to include the definition for `CvBuildingClassInfo`
        1. `src/CvGameCoreDLLPCH.h` should be updated to include `CvInfos.h`
        1. `src/CvGlobals.h` should be updated to include references for `CvBuildingClassInfo`
   - Do not:
     - Add extra imports that were not in the source files
     - Add extra structures to create padding for ABI compatibility

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

1. Disassemble the compiled source and verify it matches the functions in the Beyond Earth game core

1. If there are functions that do not match, do not make changes to the source
   - If the differences can be explained by compiler options or other reasons not related to the source, ignore them
   - Otherwise, the functions should not be considered identical and should be removed

1. If there are any constructs (functions, classes, definitions, etc.) in a file that are not identical, evaluate changes that are needed.
   1. If the changes are minimal and can be done, do them, and add a comment indicating an overview of the differences, e.g.

   ```c++
   // Beyond Earth writes a signed version number and adds bOption3 in version 2.
   ```

   1. Otherwise, add a TODO with the construct name if the construct exists in the Beyond Earth game core, e.g.

      ```c++
      // TODO: CvPlayerManager::RefreshDangerPlots()
      ```

1. If there are any constructs that do not exist in the Beyond Earth game core, copy the construct, comment it out, and add a note, e.g.

   ```c++
   // NOTE: getWorldSizeMaxConscript does not exist in Beyond Earth game core
   // int getWorldSizeMaxConscript(const CvPolicyEntry& kPolicy);
   ```

1. Once modifications are done, mark all all modified `.cpp` and `.h` files as checked in [docs/todo.md](../todo.md) if they meet one of these criteria:
   - It is an identical match for a file in the Civ 5 game source
   - Or if the only constructs missing from the file (functions, classes, etc) do not exist in the Beyond Earth game core

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

1. If an AI agent is performing these steps, generate a document in `docs/ai` containing only the information listed below:
   - For each `.cpp` file created or modified in this project, a table containing a list of functions with columns for whether the function exists in Beyond Earth, whether the function exists in Civ 5, and if the function is identical between the two
     - For functions that are not identical, create a section below the table for each function with bullet points consisely describing the differences
   - For any other files added to or modified in the project (e.g. `.h` files), add a section with bullet points consisely describing what was added or modified, noting any significant differences between the Beyond Earth and Civ 5 source
