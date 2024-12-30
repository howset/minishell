/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:41 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/30 04:55:42 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"

void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	reset_signals(void);

#endif
