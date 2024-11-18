# Minishell

Just starting.

## Collected materials:
- https://github.com/DimitriDaSilva/42_minishell
- https://github.com/Swoorup/mysh
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

## Notes
### readline

```
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char *prompt);
```
- The line returned is allocated with malloc(3); the caller must free it when finished.