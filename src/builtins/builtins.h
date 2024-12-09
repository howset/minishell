#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

// exec.c
int is_builtin(char *cmd);
int exec_builtin(char *args[], char *envp[]);
int exec_commtab(t_commtab *table, char *envp[]);

// echo.c
int rh_echo(char *args[], int opt);

// env.c
int	rh_env(char *envp[]);

// exit.c
int	rh_exit(char *args);

#endif