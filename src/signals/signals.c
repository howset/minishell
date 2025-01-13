/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 16:43:25 by hsetyamu         ###   ########.fr       */
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
void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	t_alldata *all_data;

	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	all_data = get_alldata();
	all_data->exit_stat = 130; // 130 = Terminated by SIGINT
	//printf("all_data->exit_stat:%d\n", all_data->exit_stat);
}

/**
 * CTRL + \
*/
 void	handle_sigquit(int signum)
{
	(void)signum;
}

/**
 * CTRL + D (EOF) is handled by readline in the main loop
 * CTRL + C SIGINT
 * CTRL + \ SIGQUIT
 * SA_RESTART | SA_SIGINFO; // Restart interrupted syscalls | SA_SIGINFO to pass extra info
*/
void	setup_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
	t_alldata *all_data;
	
	all_data = get_alldata();
	
	sa_int.sa_sigaction = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa_int, NULL);
	
	//sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);

	if (all_data)
		//printf("all_data->exit_stat:%d", all_data->exit_stat);
		printf(" ");
}

