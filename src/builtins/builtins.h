#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

// echo.c
int		rh_echo(char *args[]);
int		check_n(char *arg);
int		writing(char *str);

// env.c
int		rh_env(char *args[], char *envp[], t_env **env_list);
void	init_envlist(t_env **env_list, char *envp[]);
void	free_envlist(t_env *env_list);
t_env	*find_env(t_env *env_list, char *key);
void	update_env_variable(t_env *env_list, char *key, char *val);

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
void	print_sortedenvlist(t_env *env_list);

// unset.c
int		remove_envvar(char *key, t_env **env_list);
int		rh_unset(char *args[], t_env **env_list);

// pwd.c
int		rh_pwd(void);
int		rh_cd(char *path);

#endif
