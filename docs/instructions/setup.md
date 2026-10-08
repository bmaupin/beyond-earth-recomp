# Setup

## Prerequisites

- You must own Civilization V and Civilization: Beyond Earth with all expansions (other DLC not necessary)

## Steps

1. Install Docker

   ⓘ The build tools used to build the game core will be run in a container image to ensure matching binary output; by validating that the binary output matches, it confirms the source code matches
   - Linux: Follow the steps here: https://docs.docker.com/engine/install/
   - Mac/Windows: Use https://docs.docker.com/desktop/

1. Download and install these in Steam
   - Sid Meier's Civilization V
     - This will be used as a reference since the Lua code in the game calls the game core code
   - Sid Meier's Civilization V SDK (listed under _Tools_)
     - This contains the Civ 5 game core source code
   - Sid Meier's Civilization Beyond Earth
     - This will be used as a reference since the Lua code in the game calls the game core code

1. Download Beyond Earth game core (libCvGameCoreDLL_Expansion1.so)

   ⓘ The Linux version of the game core is used as a reference, because unlike the Windows game core, it contains additional information that can be used in reconstructing the original source code (function names, debug symbols, etc)
   1. Open Steam

   1. Go here in a web browser: https://steamdb.info/depot/328351/manifests/

   1. Click on the copy icon to the right of the top manifest (to the right of _6811920298029124785_)

   1. In the popup, click _Open Steam console_

   1. Press Ctrl+V to paste the command from your clipboard and press Enter to run it

   1. It will download the Beyond Earth Linux executable depot and give you the location of the files

   1. Go to that location (in a terminal or file browser) and copy `libCvGameCoreDLL_Expansion1.so` to `private/beyond-earth/` in this project (create the directories as needed)

1. Download Civ 5 game cores

   ⓘ These are used as a reference to compare Civ 5 and Beyond Earth; if the code in the game core matches for a particular function, we know the source code from the Civ 5 SDK can be used for Beyond Earth without any changes.
   1. Open Steam

   1. Go here in a web browser: https://steamdb.info/depot/282301/manifests/

   1. Click on the copy icon to the right of the top manifest (to the right of _5267780777055206315_)

   1. In the popup, click _Open Steam console_

   1. Press Ctrl+V to paste the command from your clipboard and press Enter to run it

   1. It will download the Civ 5 Linux executable depot and give you the location of the files

   1. Go to that location (in a terminal or file browser) and copy these files to `private/civ5/` in this project (create the directories as needed)
      - libCvGameCoreDLL.so
      - libCvGameCoreDLL_Expansion1.so
      - libCvGameCoreDLL_Expansion2.so

1. (Recommended) Analyse the Beyond Earth game core with Ghidra

   ⓘ This is useful for reconstructing source code in the event that the Beyond Earth code differs from the Civ 5 code
   1. Download and install [Ghidra](https://github.com/NationalSecurityAgency/ghidra/)

   1. Open Ghidra, create a new project, add the Beyond Earth `libCvGameCoreDLL_Expansion1.so` file to it, open it and analyse it

1. Build the container image used to compile the game core
   - Linux:

     ```
     docker build . -t civ-recompile
     ```

   - Mac/Windows: Build the container from the `Dockerfile` in this project in Docker Desktop
