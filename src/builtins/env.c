/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:33:54 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/12 23:00:47 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

static void	rh_env_g(char *envp[])
{
	int	i;

	i = 0;
	printf("-->The following are the global variables environ.<--\n");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

/**Iterates the envp that is passed from the calling terminal (environ) and
 * prints row by row. When no option is given, then prints the variables in
 * **this** minishell, when `-g` is given, then prints the global environ
 * variables.
 * 		Takes basically everything (args for the option, envp, and env_list).
 * 		Returns a zero because always success.
 */
int	rh_env(char *args[], char *envp[], t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	if (!args[1])
	{
		while (temp)
		{
			if (!ft_strcmp(temp->key, "?"))
			{
				temp = temp->next;
				continue ;
			}
			if (temp->val)
				printf("%s=%s\n", temp->key, temp->val);
			else
				printf("%s=\n", temp->key);
			temp = temp->next;
		}
	}
	else if (ft_strncmp(args[1], "-g", 2) == 0)
		rh_env_g(envp);
	else
		printf("No option or option -g only");
	return (EXIT_SUCCESS);
}
