
### 25.12.2024
- I merged the parser tests from r-parser to main and deleted the branch.
- I finished `pwd` and `cd` builtins.
- Wrote tests for all builtins, except `exit` because it's tricky.
- Merge h-builtins to main and deleted h-builtins.
- Added tests for command table.
	- while doing so, I found a bug in handling `or` in command table. I fixed it


### 26.11.2024
- fixed lex_word.
- fixed a bug in when starting with a symbol. Like `()` would fail.
- added automated unit tests for lexer. run `make test` to run tests for lexer.
- refactored lexer to be more modular
- cleaned up some code and removed unnecessary files
- finished norminetting the lexer

### 25.11.2024
- lex_word is faulty, why? -- must recheck
- better way to handle quotes --> blocking operation?
- best way to comment functions? --> ask reem
- test further? --> seems ok though
- doubly linked list?

### 21.11.2024
- tried to simplify lexer to tokenize string from readline to just words and metachars.
- failed spectacularly in malloc-ing the array and free-ing them.
- a frankenstein function now, but seems working.
- next: categorize further (from TKN_WORDS) OR just tokenize further (to other TKN_s).

### 22.11.2024
- Keep makefile as it is, if there is a problem, change to use wildcards (?)
- expand tokens to specify things further.
- start with wrapper functions to save lines.
- must recode the lexer to get rid of the fixed array tokens.
- also a good idea to start specifying the tokens.

### 25.11.2024
- lex_word is faulty, why? -- must recheck
- better way to handle quotes --> blocking operation?
- best way to comment functions? --> ask reem
- test further? --> seems ok though
- doubly linked list?

### 26.11.2024
- start a parsing branch.
- whooooo this is confusing. the code seems to work but i have no idea how.

### 27.11.2024
- got a more or less ok starting pont for the parser.
- target is to make an ast?
- hint from M&M: dont conflate execution with parsing. Remember the aim of parsing.

### 3.12.2024
- Reem successfully finished the parser, only have to conform to norm now
	- input: rename the func `parse` to `parser`, uniform with `lexer`
	- input: specify `tkn_type` & `nd_type` instead of just `type` in the corresponding structs, make them easier to identify in the functions
	- ask: how to process heredoc?
	- ask: how about other brackets? '[', ']', '{', '}'?
	- ask: how about quotes?
	- free the ast by the end of main?
- Howard just made slides for selfish purposes
	- Add one more slide with even shortened funcs for better flow
	- Mess around with command tables
- command table --> done but seems unuseful
- builtins (echo, cd, pwd, export, unset, env, exit)
- try execve/execvp
- signals (ctrl-c)
- read fork, dup, pipe
- `ls -l >> output.txt | grep words > input.txt`

### 4.12.2024
- Ask reem:
	- How to fix Makefile: make does not recompile for minor change in source file
	- `consume_token` & `get_token_type` in parser_utils.c can be deleted?
- To do:
	- echo:
		- Exit status on echo?
		- More tests for echo
		- Remove trailing space?

### 5.12.2024
- Plan:
	- Make comments, then next time read each other's
	- Fix problems with makefile:
		- recompilation --> done
		- re rule
	- make/add ft_realloc to work around realloc
	- start with `free` --> Howard will NOT touch this until kingdom comes
	- handle quotes properly in parser

### 6.12.2024
- pushed ft_realloc to main
- lexer: unexit the shell for unterminated quotes --> push to main?
- parser: command node accepts quotes, not just words --> push to main?
- parser: takes TK_BG as args
- comm tab: if "&" by the end of args, set is_bg to 1.
- maybe reem pulls from h-echo to r-parser before working because there are already a couple of changes on parser and lexer.
- input for streamlining & norms: how to print errors? fprintfs (e.g. syntax_error_at) or perrors (malloc_perex)?
- early implementation of env.
- overhauled echo to use write instead of printf.
- trying exit status &$?

### 9.12.2024
- Extend `echo` to manage quotes
- Not sure how to consolidate command table from 2 different branches.
	- Maybe take the more sophisticated one?
- exit:
	- exit bb 35:
		- bash: angry with numeric argument & then exit
		- minishell: too many args & exit
	- the rest seems okay

### 10.12.2024
- exit: now works properly
- echo: now works properly
- env: now works properly
- implement `ft_fprintf` separately in src/utils
- make new branch to start export & unset: h-export_unset
- unset: ???
- export:
	- has list/table of system envvar
	- still has to work it though

### 11.12.2024
- export: seems to be working now. The functions are scattered though between env.c, and export.c. The main (in minishell.c) is a mess.
	- should the printed out vars be sorted alphabetically?
- env: fix env where LS_COLORS cant be printed out properly due to having multiple '=' in the val (no more ft_split).
	- added option -g to print the envp. The default prints the env_list.
- tried to make it consistent, perror for failed system calls, custom errors with ft_fprintf.
- unset: seems working.
- A new branch h-fork to experiment with forking. Deletes h-echo & h-env_exit from the remote to avoid a mess.

### 12.12.2024
- The forking and execve seems working, but the generated fucntion seems very messy.
- Next:
	- seems like a good idea to pause and review, then shorten the ones with too many lines. It's already quite a lot at this point.
	- or just make efforts to valgrind stuffs up.

### 16.12.2024
- Consolidation Reem & Howard: review & next agenda

### 17.12.2024
- Revamp main in minishell.c & struct.h.
	- Have a t_alldata struct that contains all other structs to make the code looks cleaner.
	- all functionalities seems preserved.
- Changes in rh_env, remove quotes in printing.
- Got some idea to implement autocompletion, but only for path and directories, not for non-builtin commands.
	- Scratch this, autocompletion for path and dirs is somehow already baked-in inside readline.
	- nonbuilt-in commands require forbidden funct (rl_attempted_completion_function, rl_completion_matches()).
- history now dont save empty lines

### 18.12.2024
- make `export` prints out sorted env. --> now 2 files, export.c and export_sort.c
- free `env_list` in main.
- separate `find_path` in exec.c to a couple of smaller functions.
- separate `exec_prog` in exec.c to a couple of smaller functions.
- shorten `exec_builtin` in exec.c, transfer lines to `rh_echo` in echo.c.
- echo now deals with edge case `echo -nnnn -n -n teststr`.
- it seems that nobody handles the issue with echo -n something and readline/history.
- before forget: the handling of quotes in echo is wrong!!! --> fix!!!!

### 20.12.2024
- reem works parser in h-fork
- howard make new branch h-builtins
	- exec as a new module
