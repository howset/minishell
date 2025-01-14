/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 10:43:41 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

t_env	**g_env;

/**
 * CTRL + C
*/
void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		add_envvar(g_env, "?", "130");
	}
	//g_signal_stat = 128 + SIGINT;
}

/**
 * CTRL + \
*/
/*  void	handle_sigquit(int signum)
{
	(void)signum;
} */

/**
 * CTRL + D (EOF) is handled by readline in the main loop
 * CTRL + C SIGINT
 * CTRL + \ SIGQUIT
 * SA_RESTART | SA_SIGINFO; // Restart interrupted syscalls | SA_SIGINFO to pass extra info
*/
void	setup_signals(t_env **env)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
	
	g_env = env;
	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	
	//sa_int.sa_handler = handle_sigint;
	sa_int.sa_sigaction = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa_int, NULL);
	
	sa_quit.sa_handler = SIG_IGN;
	//sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

