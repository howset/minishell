/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:41:43 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/15 17:42:30 by reldahli         ###   ########.fr       */
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
