/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:00:04 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 14:57:40 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include <limits.h>

#include "builtins.h"

/*
 * To imitate the real exit:
 *	1. If no args, then exit(0).
 *	2. If args is not numeric, then give error msg, and exit(2).
 * 		- Incl. detail checks for invalid numbers (0 or INT_MAX).
 *	3. If more than 1 args, then give error msg and return but dont exit.
 *	4. Otherwise, exit with args.
 * 		Takes args
 * 		Return nothing i guess (?). Just exit.
 */

int	rh_exit(char *args[])
{
	int	exit_stat;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!ft_isnumber(args[1]))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			args[1]);
		exit(2);
	}
	exit_stat = ft_atoi(args[1]);
	if ((exit_stat == 0 && ft_strncmp(args[1], "0", 1) != 0)
		|| exit_stat > INT_MAX || exit_stat < INT_MIN)
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			args[1]);
		exit(2);
	}
	if (args[2])
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (1);
	}
	exit(exit_stat);
}
