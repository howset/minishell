/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/10 19:43:55 by hsetyamu         ###   ########.fr       */
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
void	handle_sigint(int signum)
{
/* 	(void)sig;
	write(STDERR_FILENO, "\nrh-shell> ", 11);
	//rl_on_new_line(); //remove redundant prompt
	//rl_replace_line("", 0);
	rl_redisplay(); */
	/* (void)sigint;
	write(STDERR_FILENO, "\nrh-shell> ", 11); */
	//write(STDERR_FILENO, "\nrh-shell> ", 11);
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//g_flag = signum;
	}
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
/* 	//disable_ctrl_char_echo();
	signal(SIGINT, handle_sigint); // Handle ctrl-C
	signal(SIGQUIT, handle_sigquit); // Handle ctrl-\
	// ctrl-D (EOF) is handled by readline in the main loop */
	
	struct sigaction sa;
	
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // Restart interrupted syscalls
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}

