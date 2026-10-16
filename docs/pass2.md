# Pass 2: Start implementing remaining functions

## Goal

The goal of this pass is to copy remaining functions from the Civ 5 game core source and implement the changes.

- The machine code must match after normalising relocation-dependent addresses and symbol references
- Normalisation must preserve referenced targets and must not hide differences in instructions, control flow, constants, or field offsets

"Matching" in this document refers to code that meets the goals for this pass as described in this section.

1. For a particular source file, look for any functions that are marked with a TODO, indicating they are not yet implemented

1. If the function exists in the Civ 5 game core source, copy it as-is to an identically named file in [`src/`](../src/)

1. Compile the source, e.g.

   ```
   docker run --rm \
     -v "$PWD:/work" \
     -w /work \
     civ-recompile \
     /clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04/bin/clang++ \
     -std=c++11 -m32 -Os -fPIC \
     -isystem /clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04/include/c++/v1 \
     -Isrc \
     -Isrc/Fireworks \
     -Isrc/CvGameCoreDLLUtil \
     -Isrc/CvGameCoreDLLUtil/include \
     -c src/CvGameCoreEnumSerialization.cpp \
     -o private/build/CvGameCoreEnumSerialization.o
   ```

1. Disassemble the compiled source and compare the relevant section of the Beyond Earth game core to determine the differences and changes that need to be made
   - If the changed or new regions for a function or other construct contain more than 100 machine instructions in total that need to be implemented (excluding alignment padding), confirm first before implementing the changes

1. Modify the function as necessary so that the assembly matches as per the goal listed above
   - Add a comment indicating an overview of the differences, e.g. if the difference is in the function:

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

1. Once the changes are made, compile the source again and compare against the Beyond Earth game core binary. Repeat as necessary until the machine code matches according to the definition above.

1. Continue to the next function in the source file
