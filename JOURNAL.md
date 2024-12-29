Bugs found:
- Double quotes in echos. For example `echo "a \n b" will output `a \n b` instead of `a` and `b` on separate lines. This is probably to be handled in the parser.

TODO:
- refactor `exec_chprocess` and move the builtin check to `exec_chprocess`
- handle redirections

### 29.12.2024
- The redirections should redirect the file output into a file or append it to a file. Any command can have redireection even if it's a builtin command. I'm thinking that the best place to handle this would be the place that will execute the command. AKA. `exec_chprocess`. If we handle it here, any command having direction will work with minimal effort. As a start, I need to refactor it to run all the commands first.
	- ✅ Moved the builtins check and execution to `exec_chprocess`
- Next step is to handle redirections. I'll start with handling `>` and `>>`. I'll start with `>` and then move to `>>`.
	- While testing more complex scenarios. In particular, redirections with pipes `ls -l | grep a > output.txt`. I found that we had a bug in command table while handling redirections nodes in pipe nodes. ✅  I fixed this bug and added a test case for it.
	- ✅ To allow exec_chprocess to handle redirections, it needs to know the redirections. I'll update the function to take the `t_command` struct as an argument. This way, it can access the redirections.
### 28.12.2024
- Improved command tables testing so it uses the whole flow of lexer -> parser -> command table -> exec. This way we can test the whole flow of the shell.
- QUESTION: do we need to handle subshell? It's not covered in parsers. will come back to this later.
- I need to handle replacments, for example replacing a variable with its value. I believe the best place to do this woiuld be in the parser. We already have a token with type `TKN_VAR` that we can use for this.
	- To do this, I need to be able to seach for env variables in the parser. The code we use to handle this is in the builtin modul and it's scattered. I need to move this code to a separate module, group it together and make it more modular. I'll then use this module in the parser to handle replacements. It will still used as it is in the builtin module.
- ✅ moved env variables code to a separate module
- Using the env in the parser is not as easy as it sounds. The reason is the env variables is part of all_data struct, which is not available in the parser. I passed the all_data struct to the parser, but it's not a good idea to pass it to the parser. I need to find a better way to handle this. I'll come back to this later. but for now env replacment works with `echo $HOME` . Variables inside quotes are not handled yet.
- done environment variable replacement in parser. It works with `echo $HOME` and `echo "$HOME"`. In the process, I fixed the bug with hanlding double quotes. The code now handles double quotes properly. So now when doing ` echo "hello world"`, it will work properly.
- ✅ fixed bug in `export` where it doesn't accept values with double quotes. For exmaple `export HOME="hello world"` will not work. Now it works.

### 26.12.2024
- Replaced first iteration of command table with command table of `r-command-table` branch
- Finished first iteration of handling pipes. Tested the code with 3 pipes and it works. EG. `ls -l | grep a | wc -l`
- Found an issue with our code flow, Pipes doesn't work if it contains a builtin command. EG. `ls -l | echo hello | wc -l` will not work. The reason is that we check if a command is a builtin command and execute it before we check if it's a pipe command. We need to change the order of the checks. We also lack pipes redirections in this case.
- Next step: Move the builtin check to exec_chprocess function, so it doesn't matter if the command is a builtin or not. We can then check if the command is a pipe command and handle it accordingly. May also comeup with a better name
- Found a bug in handling doubles quotes, like in grep` "hello world"`. The code doesn't handle it properly. Need to fix it.


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
