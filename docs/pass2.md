TODO: Finish this document

1. If the functions do not match, or the functions only exist in Beyond Earth and not Civ 5, take action depending on the level of source to reconstruct that was decided above
   - _Only identical code_:
     - Do not implement the function

   - _All source_:
     - On the first pass, if there are any functions that do not generate matching source code as per the definition listed above under [Goal](#goal), determine the number of total total instructions and new or changed instructions
     - Then decide in which order to implement the functions based on number of instructions to implement

   - _Limited modifications_:
     - If the changed or new regions for a function or other construct contain more than 10 machine instructions in total that need to be implemented (excluding alignment padding), do not implement it

1. Then make the changes
   - If a function or other construct does not match and is not yet to be implemented, add a TODO with the declaration and number of total instructions and new or changed instructions:

     ```c++
     // TODO: CvPlayerManager::RefreshDangerPlots() (137 total instructions, 101 new or changed)
     ```

     Then skip the steps below and instead move to the next function

   - When implementing a function that differs, add a comment indicating an overview of the differences, e.g. if the difference is in the function:

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
