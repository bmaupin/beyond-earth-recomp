# Recompile a source file

1. Pick a file to recompile
   - Pick a file from [todo.md](todo.md) or [status.md](status.md)

1. Compare the file to Civ 5 game core source for a baseline, e.g.

   ```
   ./scripts/compare-file-to-civ5.sh DiplomacyAI.cpp
   ```

1. If using an AI agent, open [pass1.md](pass1.md) and have it implement functions in that source file that match the Civ 5 source
   - This can probably be done with a lower model, such as GPT Luna or Claude Haiku

1. Then open [pass2.md](pass2.md) and have it implement remaining functions in that source file

1. Compare the generated binary file with the Beyond Earth source

   ```
   ./scripts/compare-file-to-beyond-earth.sh private/build/CvDiplomacyAI.o
   ```

1. Update [status.md](status.md) with the recompilation progress of the file
