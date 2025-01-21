/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:41:43 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/21 18:33:59 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"

// this aims to free the mallocs from create_envvar
void	free_envlist(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->val)
			free(tmp->val);
		free(tmp);
	}
}

t_env	*copy_envlist(t_env *src)
{
	t_env	*new_list;
	t_env	*current;
	t_env	*temp;

	if (!src)
		return (NULL);
	new_list = NULL;
	current = src;
	while (current)
	{
		temp = create_envnode(current->key, current->val);
		if (!temp)
		{
			free_envlist(new_list);
			return (NULL);
		}
		temp->next = new_list;
		new_list = temp;
		current = current->next;
	}
	return (new_list);
}

t_env	*create_envnode(char *key, char *val)
{
	t_env	*temp;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return (NULL);
	temp->key = ft_strdup(key);
	if (!temp->key)
	{
		free(temp);
		return (NULL);
	}
	if (val)
	{
		temp->val = ft_strdup(val);
		if (!temp->val)
		{
			free(temp->key);
			free(temp);
			return (NULL);
		}
	}
	else
		temp->val = NULL;
	temp->next = NULL;
	return (temp);
}
