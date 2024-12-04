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
