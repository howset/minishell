/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:41 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 23:09:46 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# define _XOPEN_SOURCE 700 // sigaction, in conjunction with signal.h

# ifndef ECHOCTL
#  define ECHOCTL 0x40
# endif

# include "../minishell.h"

void	setup_signals(t_env **env);
void	handle_sigint(void);
void	handle_sigquit(void);
void	handle_signals(int signum);
void	disable_echoctl(void);
#endif
