/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:02:56 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/21 15:07:39 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	refresh_signals(t_alldata *all_data)
{
	char	*exit_stat_str;

	exit_stat_str = ft_itoa(g_exit_stat);
	if (g_exit_stat == 130)
	{
		add_envvar(all_data->env_list, "?", exit_stat_str);
		g_exit_stat = 0;
	}
	free(exit_stat_str);
}
