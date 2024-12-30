/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:25:13 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/30 15:14:03 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	rh_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf("pwd: error retrieving current directory \n");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

int	rh_cd(char *path)
{
	char	*home;

	if (!path)
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		path = home;
	}
	if (chdir(path) != 0)
	{
		ft_fprintf(STDERR_FILENO, " No such file or directory\n", path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
