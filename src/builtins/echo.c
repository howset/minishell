/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:34:28 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 18:36:56 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	rh_echo(char *args[])
{
	int	i;
	int	opt;
	int	first_arg;

	opt = 0;
	i = 1;
	while (args[i] && check_n(args[i]))
	{
		opt = 1;
		i++;
	}
	first_arg = 1;
	while (args[i])
	{
		if (!first_arg)
			writing(" ");
		writing(args[i]);
		first_arg = 0;
		i++;
	}
	if (!opt)
		return (writing("\n"));
	return (EXIT_SUCCESS);
}

int	check_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	writing(char *str)
{
	if (write(STDOUT_FILENO, str, ft_strlen(str)) == -1)
	{
		perror("echo: write error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
