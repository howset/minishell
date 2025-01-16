/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:37:26 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/15 17:52:37 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"

void	parse_envvar(char *env, char **key, char **val)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
	{
		ft_fprintf(STDERR_FILENO, "Failed to find equal sign.\n");
		*key = NULL;
		*val = NULL;
		return ;
	}
	*key = ft_substr(env, 0, equal_sign - env);
	if (!*key)
	{
		perror("Memory allocation failed for key");
		*val = NULL;
		return ;
	}
	*val = ft_strdup(equal_sign + 1);
	if (!*val)
	{
		perror("Memory allocation failed for val");
		free(*key);
		*key = NULL;
	}
}

void	init_envlist(t_env **env_list, char *envp[])
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	while (envp[i])
	{
		parse_envvar(envp[i], &key, &val);
		if (key && val)
		{
			add_envvar(env_list, key, val);
			free(key);
			free(val);
		}
		i++;
	}
}

// swap two nodes
void	swap_envvar(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_val;

	temp_key = a->key;
	temp_val = a->val;
	a->key = b->key;
	a->val = b->val;
	b->key = temp_key;
	b->val = temp_val;
}

// sort alphabetically (by key) --> bubble sort
void	sort_envlist(t_env **env_list)
{
	t_env	*current;
	t_env	*next;
	int		swapped;
	int		key_len;

	if (!env_list || !*env_list)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *env_list;
		while (current && current->next)
		{
			next = current->next;
			key_len = ft_strlen(current->key) + 1;
			if (ft_strncmp(current->key, next->key, key_len) > 0)
			{
				swap_envvar(current, next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}

// print the sorted environment list
void	print_sortedenvlist(t_env *env_list)
{
	if (!env_list)
		return ;
	sort_envlist(&env_list);
	while (env_list)
	{
		if (env_list->val)
			printf("declare -x %s=\"%s\"\n", env_list->key, env_list->val);
		else
			printf("declare -x %s=\"\"\n", env_list->key);
		env_list = env_list->next;
	}
}
