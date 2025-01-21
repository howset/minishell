/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:41 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/21 14:31:36 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# define _XOPEN_SOURCE 700 // sigaction, in conjunction with signal.h

# ifndef ECHOCTL
#  define ECHOCTL 0x40
# endif

# include "../minishell.h"

extern int g_exit_stat;

void	setup_signals(t_env **env);
void	handle_sigint(void);
void	handle_sigquit(void);
void	handle_signals(int signum);
void	disable_echoctl(void);
#endif
