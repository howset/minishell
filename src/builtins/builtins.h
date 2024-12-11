#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

// exec.c
int	is_builtin(char *cmd);
int	exec_builtin(char *args[], t_env **env_list, char *envp[]);
int	exec_commtab(t_commtab *table, t_env **env_list, char *envp[]);

// echo.c
int	rh_echo(char *args[], int opt);

// env.c
int		rh_env(char *args[], char *envp[], t_env **env_list);
void	init_envlist(t_env **env_list, char *envp[]);
void	free_envlist(t_env *env_list);

// exit.c
int	rh_exit(char *args[]);

// export.c
void	add_envvar(t_env **env_list, const char *key, const char *val);
t_env	*create_envvar(const char *key, const char *val);
t_env	*find_envvar(t_env *env_list, const char *key);
void	print_envlist(t_env *env_list);
int	rh_export(char *args[], t_env **env_list);

// unset.c
int	rh_unset(char *args[], t_env **env_list);

#endif