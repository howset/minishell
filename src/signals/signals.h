/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:41 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/08 13:25:10 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"

void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
//void	reset_signals(void);

#endif
