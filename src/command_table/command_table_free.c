/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 23:23:03 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

void	free_command_table(t_cmdtable *table)
{
	if (!table)
		return ;
	free_command(table->commands);
	free(table);
}
