# Recompile identical functions

1. Determine the next function to recompile
   1. Look at the file timestamps in [`src/`](../../src/) and the commit history to determine the most recent file and function that was recompiled

   1. Open that file in the Civ 5 game core source to determine if all functions in that file have been recompiled. If not, pick the next function in that file.

   1. If all functions in that file have been recompiled start at the top of the list of _Implementation files_ in [todo.md](../todo.md) and pick the next file

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

1. If there are any constructs (functions, classes, definitions, etc.) in a file that are not identical, evaluate changes that are needed and add a TODO with the construct name if the construct exists in the Beyond Earth game core, e.g.

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
