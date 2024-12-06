#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

// exec.c
int is_builtin(char *cmd);
int exec_builtin(char *args[]);
int exec_singlecomm(t_simcomm *cmd);
int exec_commtab(t_commtab *table);

// echo.c
int echo(char *args[], int opt);

// exit.c

#endif