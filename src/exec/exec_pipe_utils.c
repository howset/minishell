/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:46:33 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:47:40 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

t_command	*find_last_pipe_cmd(t_command *cmd)
{
	t_command	*last_cmd;

	last_cmd = cmd;
	while (last_cmd->next && last_cmd->next->type == CMD_PIPE)
		last_cmd = last_cmd->next;
	return (last_cmd);
}

