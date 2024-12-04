#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

// exec.c
int is_builtin(char *cmd);
void exec_builtin(char *args[]);
void exec_singlecomm(t_simcomm *cmd);
void exec_commtab(t_commtab *table);

// echo.c
void echo(char *args[], int opt);

// exit.c

#endif