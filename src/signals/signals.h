/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:41 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 16:42:59 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# define _XOPEN_SOURCE 700 // sigaction, in conjunction with signal.h

# include "../minishell.h"

//void	setup_signals(t_alldata *all_data);
void	setup_signals(void);
void	handle_sigint(int signum, siginfo_t *info, void *context);
void	handle_sigquit(int signum);
//void	reset_signals(void);
void set_alldata(t_alldata *all_data); //currently in minishell.c
t_alldata *get_alldata(void); //currently in minishell.c
#endif
