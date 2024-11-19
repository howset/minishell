# Minishell

## Notes
### 15.11.2024
Just starting.

### 18.11.2024
- Bare minimal working example;
	- store readline in `input`
	- printf to terminal the content of `input`
	- exit cleanly
- How to store?
	- Ex. `cmd arg1 arg2 arg3` --> delimited by a space
	- ft_split to get an array ["cmd", "arg1", "arg2", "arg3"]
	- Just print out the array
	- Or just linked lists??
- Test with valgrind from the start ✅ --> `make test` or `make test_log`
	- reachable bytes only from `readline`
	- if used, add_history also contributes to reachable bytes
- Read and make notes of builtins, redirections, execve, environment, etc

### 19.11.2024
- git, storing things, comms

## Collected materials:
- https://github.com/DimitriDaSilva/42_minishell
- https://github.com/appinha/42cursus-03-minishell/blob/main/README.md
- https://github.com/Swoorup/mysh
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

## Scribbles
### `readline`

```
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char *prompt);
```
- source: man 3
- The line returned is allocated with malloc(3); the caller must free it when finished.

### `history`

```
typedef void *histdata_t;

typedef struct _hist_entry
{
char *line;
char *timestamp;
histdata_t data;
} HIST_ENTRY;
```
- The history list itself might therefore be declared as `HIST_ENTRY ** the_history_list;`
- The history list is an array of history entries.
- `void add_history (const char *string)`
	- Place string at the end of the history list.  The associated data field (if any) is set to NULL.  If the maximum number of history entries has been set using stifle_history(), and the new number of history entries would exceed that maximum, the oldest history entry is removed.

### Redirections & Pipes
- `<`
- `>`
- `<<` pass multiple lines of input to a command up to a certain delimiter
- `>>`
- `|`

### Allowed Funcs
| Function				| Manual Page		| From lib					| Description
| :--					| :--				| :--						| :--
| **printf**			| `man 3 printf`	| `<stdio.h>`				| write output to stdout
| **malloc**			| `man malloc`		| `<stdlib.h>`				| allocate dynamic memory
| **free**				| `man 3 free`		| `<stdlib.h>`				| free dynamic memory
| **read**				| `man 2 read`		| `<unistd.h>`				| read from a file descriptor
| **write**				| `man 2 write`		| `<unistd.h>`				| write to a file descriptor
| **open**				| `man 2 open`		| `<fcntl.h>`				| open and possibly create a file
| **close**				| `man 2 open`		| `<unistd.h>`				| close a file descriptor
| **fork**				| `man fork`		| `<unistd.h>`				| create a child process
| **wait**				| `man wait`		| `<sys/wait.h>`			| wait for process to change state
| **waitpid**			| `man waitpid`		| `<sys/wait.h>`			| wait for process to change state
| **wait3**				| `man wait3`		| `<sys/wait.h>`			| (obsolete) wait for process to change state, BSD style
| **wait4**				| `man wait4`		| `<sys/wait.h>`			| (obsolete) wait for process to change state, BSD style
| **signal**			| `man signal`		| `<signal.h>`				| ANSI C signal handling
| **kill**				| `man 2 kill`		| `<signal.h>`				| send signal to a process
| **exit**				| `man exit`		| `<stdlib.h>`				| cause normal process termination
| **getcwd**			| `man getcwd`		| `<unistd.h>`				| get current working directory
| **chdir**				| `man chdir`		| `<unistd.h>`				| change working directory
| **stat**				| `man 2 stat`		| `<sys/stat.h>`			| get file status by pathname
| **lstat**				| `man lstat`		| `<sys/stat.h>`			| get file status by pathname (for symlinks)
| **fstat**				| `man fstat`		| `<sys/stat.h>`			| get file status by fd
| **execve**			| `man execve`		| `<unistd.h>`				| execute program
| **dup**				| `man dup`			| `<unistd.h>`				| duplicate a file descriptor
| **dup2**				| `man dup2`		| `<unistd.h>`				| duplicate a file descriptor
| **pipe**				| `man pipe`		| `<unistd.h>`				| create pipe
| **opendir**			| `man opendir`		| `<dirent.h>`				| open a directory
| **readdir**			| `man readdir`		| `<dirent.h>`				| read a directory
| **closedir**			| `man closedir`	| `<dirent.h>`				| close a directory
| **strerror**			| `man strerror`	| `<string.h>`				| return string describing error number
| **errno**				| `man errno`		| `<errno.h>`				| number of last error
| **termcap**			| `man termcap`		| `<term.h>`				| direct curses interface to the terminfo capability database
| **readline**			| `man readline`	| `<readline/readline.h>`	| get a line from a user with editing
| **rl_clear_history**	| Readline Library	| `<readline/readline.h>`	| clear the history list by deleting all of the entries
| **rl_on_new_line**	| Readline Library	| `<readline/readline.h>`	| tell the update functions that we have moved onto a new (empty) line
| **rl_replace_line**	| Readline Library	| `<readline/readline.h>`	| replace the contents of rl_line_buffer with text
| **rl_redisplay**		| Readline Library	| `<readline/readline.h>`	| change what’s displayed on screen to reflect the current contents of rl_line_buffer
| **add_history**		| `man history`		| `<readline/history.h>`	| place string at the end of the history list.
| **access**			| `man 3 access`	| `<unistd.h>`				| checks whether the calling process can access the file pathname
| **sigaction**			| `man 3 sigaction`	| `<signal.h>`				| allows calling process to examine &/ specify action to be associated with a specific signal
| **sigemptyset**		| `man 3 sigsetops`	| `<signal.h>`				| initializes the signal set given by set to empty, with all signals excluded from the set
| **sigaddset**			| `man 3 sigsetops`	| `<signal.h>`				| add signal signum from set
| **unlink**			| `man 3 unlink`	| `<unistd.h>`				| remove a link to a file
| **perror**			| `man perror`		| `<stdio.h>`				| produces a message on std err describing the last error encountered
| **isatty**			| `man isatty`		| `<unistd.h>`				| test whether a file descriptor refers to a terminal (returns 1 if yes)
| **ttyname**			| `man ttyname`		| `<unistd.h>`				| returns a pointer to the null-terminated pathname of the terminal
| **ttyslot**			| `man ttyslot`		| `<unistd.h>`				| find the slot of the current user's terminal in some file
| **ioctl**				| `man 2/3 ioctl`	| `<stropts.h>`				| 
| **getenv**			| `man getenv`		| `<stdlib.h>`				| get an environment variable
| **tcsetattr**			| `man termios`		| `<unistd.h>`				| sets the parameters associated with the terminal
| **tcgetattr**			| `man termios`		| `<unistd.h>`				| gets the parameters associated with the object referred by fd and stores them
| **tgetent**			| https://linux.die.net/man/3/tgetent	| `<curses.h>` & `<term.h>`	| conversion aid for programs that use the termcap library
| **tgetflag**			| https://linux.die.net/man/3/tgetflag	| `<curses.h>` & `<term.h>`	| conversion aid for programs that use the termcap library
| **tgetnum**			| https://linux.die.net/man/3/tgetnum	| `<curses.h>` & `<term.h>`	| conversion aid for programs that use the termcap library
| **tgetstr**			| https://linux.die.net/man/3/tgetstr	| `<curses.h>` & `<term.h>`	| conversion aid for programs that use the termcap library
| **tgoto**				| https://linux.die.net/man/3/tgoto		| `<curses.h>` & `<term.h>`	| conversion aid for programs that use the termcap library
| **tputs**				| https://linux.die.net/man/3/tputs		| `<curses.h>` & `<term.h>`	| conversion aid for programs that use the termcap library