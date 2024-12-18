#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

// exec.c
int		is_builtin(char *cmd);
int		exec_builtin(char *args[], t_env **env_list, char *envp[]);
int		exec_commtab(t_commtab *table, t_env **env_list, char *envp[]);
char	*init_fullpath(t_env *env_list, size_t *path_len);
char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len);
char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len);
char	*find_path(char *cmd, t_env *env_list);
int		exec_chprocess(char **args, t_env *env_list, char *envp[]);
int		wait_chprocess(pid_t p_id);
int		exec_prog(char **args, t_env *env_list, char *envp[]);

// echo.c
int		rh_echo(char *args[]);

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
//void	print_envlist(t_env *env_list);
int		rh_export(char *args[], t_env **env_list);

// export_sort.c
void	swap_envvar(t_env *a, t_env *b);
void	sort_envlist(t_env **env_list);
void	print_envlist_sorted(t_env *env_list);

// unset.c
int		rh_unset(char *args[], t_env **env_list);

#endif