# Minishell

## About
This project was done from around November 2024 until January 2025 by [Reem](https://github.com/ReemEssamEldin) and [Howard](https://github.com/howset), and as well with many, many help from Basel.

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

## Post Eval Remarks
### H
From my part, this project was quite a challenge to do. By itself I would probably say that the project was not extraordinarily complex, however the sheer size of the project (relatively to the projects that have been done to date) made managing the whole project overwhelmingly difficult. Wrapping my head around the many things that have to work together was a major hurdle.
The way I see it, the success of the project relies very heavily on the (advanced) functionalities the parser and exec modules (incl. the command_table module), and how they work together, which would never ever be the way they are without the help from Basel.

The end-phase of the project brought about many, many tribulations, especially in regard to conforming the project to the norm. Separating the functions to meet the limit of lines per function, max declared variables, max args per function, etc., all these puts the project in a pathetic state because we (read: Howard) borked the code again and again and again. Experiment with something new, borked the code. Conform to norm, borked the code. Add new idea, borked. Luckily Reem seems to be very enlightened time and time again and managed to perform rescues and fixes.

In retrospect, I would never expect the project to be able to reach the state it's in right now, however some things that I probably would have liked to be done differently:
1. Do the subshell bonus. It was just one step away (maybe 1 or 2 days at most), but alas, by then I would have been blackholed. Maybe the other bonuses as well, but dunno.
2. Re-organize the exec modules better. Nobody in their right minds would ever name files spillover & spillover2. There was a reason for this. But not a good one.
3. Do the env module probably differently (SHLVL, initialization) and re-arrange the flow differetnly as well.
4. We wanted to put nice documentation & comments for each functions. Well, by the day before eval we were still scrambling to make haphazard fixes here and there. Soooo, there you go.
5. Remove the leftover function in the signal module.

The way we worked together in this project was rather unconventional. Instead of delineating a concrete separation of responsibilities and then converge at the end, we decided to go the other approach. We decide to do **everything** together, that way we are always on the same page at every stage of development. Every incremental development was informed and pushed to the repo for inspection and further experimentation/development by the other (by means of making a branch, whose numbers in the end turns out to grow beyond control if not for Reem's cleanup routine). Well at least that was the ideal plan. But then, suddenly being faced with a gigantic `parser` **and** `exec` leaves quite an impression on me, as it also would on anyone. Nevertheless, our communication and cooperation seems to be very much to my liking. It may not be a perfect one, but I don't think it could have gone any better.

I would love to mention here somethings about my personal relationship with the eponimous pointers, but I'm afraid that confession would shed what's left of my dignity, so I will wisely refrain.

## The Project
### 🖥️ General
This project tries hard to imitate **bash** in spirit, but in practice not entirely. There are only so many things that can be done in around 3 months (or was it 2?).

We worked on the project step-by-step from just a functional prompt by `readline` and added more and more things from there on. We followed the hints of our holy advisor to build the project by modules. As it is right now, the modules contained within the project are as follows (organized in folders/directories under `src/`):
1. lib
2. lexer
3. parser
4. command table
5. exec
6. builtins
7. envs
8. signals
9. utils

The header file for each module was intentionally put in its respective directory to avoid having to go up and down the dirs to look for it whenever it was necessary, though of course, this could be done differently should there be reasons to do otherwise.

Surprisingly, leaks seems to **not** be a major problem throughout this project (unlike some of us who are plagued by this issue to the death). File descriptor is a different topic though. I/we are not entirely sure how to approach this issue, but in the end nobody seem to care about this.

### 🖥️ Modules
#### ⚙️ Lib
The `lib` module just took `libft`, `ft_printf`, and `gnl` as it was. Along the project, some functions were refactored, some were added in to avoid pain (e.g `ft_realloc`), some were added because Howard for some reason was just a total failure and didn't have the simplest thing (`ft_strcmp`).

#### ⚙️ Lexer
The `lexer` is arguably the most well polished module. Very neatly organized and normed by Reem. It did it's job very, very well. I dont think there was a single occasion in which we had to look back and dig around the files/functions in this module. This is a testament of how stable it is.

This module is responsible in iterating over the input string and categorizing the input to tokens.

#### ⚙️ Parser
This is a big one, there is a [README](./src/parser/README.md) for the `parser` inside the directory.

#### ⚙️ Command Table
Guess what? There is also another [README](./src/command_table/README.md) for the `command table`.

I remembered this module started as something really simple to contain the AST and check the execution of some of our builtins. But then the piping. As well, the redirections. My god.

#### ⚙️ Exec
I think the idea of the `execution` module was pretty simple at first. Similar to the `command table`, just to check the workings of the builtins. Then trying to execute the non-builtins, then, again, pipes etc. It ended up to be rather large. We worked on this module up to the very end.

#### ⚙️ Builtins
There are only 7 builtins as mandated by the assignment. None were particularly complicated except perhaps `export` and `env`. For reasons that at the time were very convincing, many core functionalities that relate to the environment variables were separated to another module, `env`. What those reasons were exactly, I can't remember anymore 😑.

Maybe worth mentioning, our first implementation of `export` sorts the `env_list` directly to display the `env` sorted alphabetically. We refactored it to first make a copy, sort it, then display the copy without touching the `env_list`. Just a small detail that really doesn't matter in the grand scheme of things.

#### ⚙️ Envs
I think the highlight of of this module is the `add_envvar` function which is the most operative function. 
The `env_list` contains the variable '?' to store the `exit_status` of the last executed command.
Many more can obviously be said here but currently I have blank in my head.

#### ⚙️ Signals
I am embarassed to say that I took minitalk but I got severely confused with signalling. This is not a big module, we pushed working on this module right as we were nearing to finishing the project. 

The function `handle_sigquit2` is practically non-functional because Reem resorted to basically ignore it (`SIG_IGN`) for the most part of the program unless when necessary, at which point Reem just switched it back to default (`SIG_DFL`). Brilliant.

A global variable was used here to contain (only) the `exit_status` of the signals that can be delivered to `env_list` under the `var_key` **'?'** by means of `add_envvar` when `refresh_signals` is called at each iteration of the loop in `main`. LOL, no self-respecting person is ever gonna write a sentence like this.

#### ⚙️ Utils
This module contains helper functions.
1. Printing functions that were useful to see the `tokens`, or content of the `ast` & `comm_tab`.
2. Cleanups to free stuffs up.
3. `ft_fprintf` to not use `fprintf`. Just a reduced and modified version of `ft_printf`.
4. `malloc_perex` seems useful at first, but neither of us bothered to use it during later stages of the project 😮‍💨
5. The `prompt` was made to be a bit fancy as a workaround to deal with the problem we have with displaying the prompt when we go up and down the command history after `echo -n`. Arguably this can be made to another module by itself, especially if we worked on multiline history, but as it is right now, it is just simply too small.

### 🖥️ Other Components/Aspects
#### ⚙️ Main
As mentioned, we started just with a `main` and `readline`, then we build up, just like everybody else I imagine. At somepoint we have so many structs declared so we wrapped it all up in one giant struct `all_data`. 
Before the loop, we initialize the `env_list` by copying/inheriting the environ of the parent shell, as well as setting up the signal handlers.
We also wrap the lexing->parsing->conversion to comm_tab under an umbrella `parse` function to keep a simple approach.

-Mention other things in the loop?-

#### ⚙️ Readline
The `readline` library provides the `input` buffer and also manages `history` including `ctrl-D`. 

Efforts put into finding out how to adjust cursor placement was fruitless, hence the fancy prompt. 

We didn't bother to take care of the reachable bytes due to this library. I dont know if it is at all manageable.

#### ⚙️ Structs
We have a **lot** of `structs`. We luckily agreed early on to just keep all structs on a separate header, which I think was a good idea to have them all centralized and not strewn across everywhere, though perhaps not as modular as it could be.

#### ⚙️ Exit status
We carefully tried to manage the exit status of every command and signals that can be given to our minishell. It was a headache but I would like to say that we manage to do that in the end. 

#### ⚙️ Tests
Basel & Reem made tests for:
1. lexer
2. parser
3. comm_tab
4. builtins

## Materials
### Links
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
- https://www.cs.uleth.ca/~holzmann/C/system/shell_does_pipeline.pdf
- https://github.com/coreutils/coreutils


### Slides

Slides [README](./slides/README.md)
