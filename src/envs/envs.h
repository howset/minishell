# ifndef ENVS_H
# define ENVS_H

# include "../minishell.h"

void	add_envvar(t_env **env_list, char *key, char *val);
t_env	*create_envvar(char *key, char *val);
t_env	*find_envvar(t_env *env_list, char *key);
t_env	*find_env(t_env *env_list, char *key);
int		remove_envvar(char *key, t_env **env_list);

void	init_envlist(t_env **env_list, char *envp[]);
void	free_envlist(t_env *env_list);
void	swap_envvar(t_env *a, t_env *b);
void	sort_envlist(t_env **env_list);
void	print_sortedenvlist(t_env *env_list);

#endif
