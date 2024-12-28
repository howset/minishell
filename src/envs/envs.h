#ifndef ENVS_H
# define ENVS_H

# include "../minishell.h"

void			add_envvar(char *key, char *val);
t_env			*create_envvar(char *key, char *val);
t_env			*find_envvar(char *key);
t_env			*find_env(char *key);
int				remove_envvar(char *key);

void			init_envlist(char *envp[]);
void			free_envlist();
t_env			*get_envlist(void);
void			swap_envvar(t_env *a, t_env *b);
void			sort_envlist();
void			print_sortedenvlist();

extern t_env	*g_env;

#endif
