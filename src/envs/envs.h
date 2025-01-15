/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:37:55 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/15 17:55:10 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVS_H
# define ENVS_H

# include "../minishell.h"
//envlist.c
void	parse_envvar(char *env, char **key, char **val);
void	init_envlist(t_env **env_list, char *envp[]);
void	swap_envvar(t_env *a, t_env *b);
void	sort_envlist(t_env **env_list);
void	print_sortedenvlist(t_env *env_list);

//envvar.c
void	add_envvar(t_env **env_list, char *key, char *val);
t_env	*create_envvar(char *key, char *val);
t_env	*find_envvar(t_env *env_list, char *key);
int		remove_envvar(char *key, t_env **env_list);

//free_env.c
void	free_envlist(t_env *env_list);

#endif
