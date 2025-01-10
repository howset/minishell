/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/10 14:31:33 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

// this function probably supresses the echoing of ctrl-c, which we may not want.
/* void	disable_ctrl_char_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
} */

/**
 * CTRL + C
*/
void	handle_sigint(int sigint)
{
	(void)sigint;
	write(STDERR_FILENO, "\nrh-shell> ", 11);
}

/**
 * CTRL + \
*/
void	handle_sigquit(int sigquit)
{
	(void)sigquit;
}

/**
 * CTRL + D 
 * CTRL + C SIGINT
 * CTRL + \ SIGQUIT
*/
void	setup_signals(void)
{
	struct sigaction sa;
	
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // Restart interrupted syscalls
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigint");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, handle_sigquit); /* // Handle ctrl-\ */
}

