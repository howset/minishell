/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_spillover2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:52:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/22 17:52:30 by hsetyamu         ###   ########.fr       */
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
