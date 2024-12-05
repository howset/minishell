# Minishell

## Install Dependencies
### Macos
```bash
brew install readline
brew install check
brew install pkg-config
```

### Linux
```bash
sudo apt-get install libreadline-dev
sudo apt-get install check
sudo apt-get install pkg-config
```

## Notes
# To do

## 🌎 General
- Parsing:
	- Handle quotes
		- single: literal interpretation 
			- no variable & command substitution, no interpretation of special chars
		- double: partial interpretation ($)
			- Variable substitution: $VAR
			- Command substitution: $(command)
			- Limited interpretation of special chars
	- Handle other brackets (?)
	- What to do with heredoc (<<)?
	- Handle `$?` -> expand to the exit status of the most recently executed foreground pipeline
- Exec:
	- Add builtins
		- echo - half done. Functional but incomplete (exit status)
		- cd
		- pwd
		- export
		- unset
		- env
		- exit
	- Exec non-builtins
		- Read system calls: dup/dup2
		- Read system calls: fork
		- Read system calls: waitpid
		- Read system calls: execve
		- Read system calls: env
- When to `free` what.
- How to deal with `realloc`?
- Makefile problem: does no recompile for minor changes
- Make comments on functions. --> Take a day for streamlining & commenting?

## 🌴 Main
- stable

### 🌿 Branch: tokens
- 26.11.2024 - stable & merged to main

### 🌿 Branch: h-parse
- 3.12.2024 - add `comm_table.c` under src/parser/
	- Maybe unnecessary, but works.
- Pull from main the stable ast parser.
- Then merge to main the command table parser.

### 🌿 Branch: r-parser
- 1.12.2024 - parser done!
	- Delete `consume_token`& `get_token_type`? 
	- If agreed, specify `tkn_type` & `node_type` in corresponding structs.
	- If agreed, change `parse()` to `parser()`.
- Merge the stable ast parser to main.

### 🌿 Branch: h-echo
- 3.12.2024 - start with echo
	- How to deal with exit status?
	- How to remove trailing space?
- Pull from main the stable ast and comm table parser
- Still have to polish exec.c

## Collected materials:
- https://github.com/DimitriDaSilva/42_minishell
- https://github.com/appinha/42cursus-03-minishell
- https://github.com/twagger/minishell
- https://github.com/LeaYeh/minishell
- https://github.com/Swoorup/mysh
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
- https://brennan.io/2015/01/16/write-a-shell-in-c/
- https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/
- https://www.gnu.org/software/bash/manual/html_node/Definitions.html
- https://www.youtube.com/watch?v=ZjzMdsTWF0U
- https://www.youtube.com/watch?v=ubt-UjcQUYg
- https://www.youtube.com/watch?v=SToUyjAsaFk

## Scribbles
- dup vs dup2: duplicate a file descriptor. dup uses the lowest-numbered unused file descriptor, dup2 uses the file descriptor number specified in newfd.
On  success, these system calls return the new file descriptor.  On error, -1 is returned, and
       errno is set appropriately.
```
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

- fork: creates a new process by duplicating the calling process. On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On failure, -1 is returned in the parent, no child process is created, and errno is set appropriately.
```
pid_t fork(void);
```
- wait vs waitpid:  wait for state changes in a child of the calling process, and obtain information about the child whose state has changed (child termination, stopped by signal, resumed by signal). wait() suspends execution of calling thread until one of its children terminates (returns the process ID of the terminated child on success; on error, -1). waitpid() suspends execution of calling thread until a child specified by pid has changed state (can be modified) (returns 0 on success or if WNOHANG was specified and no child(ren) specified by id has yet changed state; on error, -1.).
```
#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
```


### Slides
Contains redundant content

![Parsing1](./slides/Ms_slide0.svg "Parsing")
![Parsing2](./slides/Ms_slide1.svg "Lexer")
![Parsing3](./slides/Ms_slide2.svg "Parser")
![Parsing4](./slides/Ms_slide3.svg "Parser Ex1")
![Parsing5](./slides/Ms_slide4.svg "Parser Ex2")
![Parsing6](./slides/Ms_slide5.svg "Nodes")
![Parsing7](./slides/Ms_slide6.svg "ASTree & Command Table plan")
![Parsing8](./slides/Ms_slide7.svg "Lex Syn Sem Analysis")
![Parsing9](./slides/Ms_slide8.svg "parse_expression1")
![Parsing10](./slides/Ms_slide9.svg "parse_expression2")
![Parsing11](./slides/Ms_slide10.svg "parse_expression3")
![Parsing12](./slides/Ms_slide11.svg "parse_expression4")
![Parsing13](./slides/Ms_slide12.svg "Shortened funcs")
![Parsing13](./slides/Ms_slide13.svg "Parsing workflow")
![Parsing14](./slides/Ms_slide14.svg "AST -> Command Table flow")

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
