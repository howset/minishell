/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_spillover2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:52:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/22 21:02:25 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	wait_for_children(int *status)
{
	pid_t	p_id;

	while (1)
	{
		p_id = wait(status);
		if (p_id <= 0)
			break ;
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
	return (*status);
}

int	check_logicopnode(t_command **cmd, int exit_stat)
{
	if ((*cmd)->next_opnode == NODE_AND)
	{
		if (exit_stat != 0)
		{
			while (*cmd && ((*cmd)->next_opnode == NODE_AND
					|| (*cmd)->next_opnode == NODE_OR))
				*cmd = (*cmd)->next;
			if (*cmd)
				*cmd = (*cmd)->next;
			return (1);
		}
	}
	else if ((*cmd)->next_opnode == NODE_OR)
	{
		if (exit_stat == 0)
		{
			while (*cmd && ((*cmd)->next_opnode == NODE_AND
					|| (*cmd)->next_opnode == NODE_OR))
				*cmd = (*cmd)->next;
			if (*cmd)
				*cmd = (*cmd)->next;
			return (1);
		}
	}
	return (0);
}
