#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

// echo.c
int		rh_echo(char *args[]);
int		check_n(char *arg);

// env.c
int		rh_env(char *args[], char *envp[], t_env **env_list);
void	init_envlist(t_env **env_list, char *envp[]);
void	free_envlist(t_env *env_list);

// exit.c
int		rh_exit(char *args[]);

// export.c
void	add_envvar(t_env **env_list, char *key, char *val);
t_env	*create_envvar(char *key, char *val);
t_env	*find_envvar(t_env *env_list, char *key);
int		rh_export(char *args[], t_env **env_list);

// export_sort.c
void	swap_envvar(t_env *a, t_env *b);
void	sort_envlist(t_env **env_list);
void	print_envlist_sorted(t_env *env_list);

// unset.c
int		remove_envvar(char *key, t_env **env_list);
int		rh_unset(char *args[], t_env **env_list);

#endif