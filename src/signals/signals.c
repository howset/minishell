/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/08 18:16:46 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

// this function probably supresses the echoing of ctrl-c, which we may not want.
void	disable_ctrl_char_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\nrh-shell> ", 11);
	//rl_on_new_line(); //remove redundant prompt
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// Do nothing for ctrl-\ in interactive mode.
}

void	setup_signals(void)
{
	disable_ctrl_char_echo();
	signal(SIGINT, handle_sigint); // Handle ctrl-C
	signal(SIGQUIT, handle_sigquit); /* // Handle ctrl-\ */
	// ctrl-D (EOF) is handled by readline in the main loop
}

/* void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
} */
