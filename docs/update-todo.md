# Update todo.md

Use these instructions for updating [todo.md](./todo.md)

1. If a file has a TODO, this means it is not finished; skip remaining steps

1. If a file has no TODOs, this should mean that all functions in the file are implemented and all of the source code when compiled results in machine code that matches the Beyond Earth game core binary

1. Update the Progress in [docs/todo.md](../todo.md)
   1. Calculate the number of recompiled functions of files that are finished

      ```
      pushd src 2>/dev/null &&
        cat ../docs/todo.md | grep '\[x\]' | awk '{print $3}' |
        ctags --quiet \
          --languages=C++ \
          --kinds-C++=f \
          -f - \
          -L - |
        awk -F '\t' '$4 == "f" { count++ } END { print count + 0 }';
        popd 2>/dev/null
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
      - Once progress is > 10%, change the colour to orange
      - Once progress is > 50%, change the colour to yellow
      - Once progress is > 99%, change the colour to green

   1. Do not make other modifications to docs/todo.md

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
   - Do not include other information in the file
   - If a file is created, provide a link
