/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 18:31:44 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

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
	}
	g_signal_stat = 128 + SIGINT;
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
void	setup_signals(t_alldata *all_data)
{
	struct sigaction sa_int;
	//struct sigaction sa_quit;
	
	ft_memset(&sa_int, 0, sizeof(sa_int));
	//ft_memset(&sa_quit, 0, sizeof(sa_quit));
	
	sa_int.sa_sigaction = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa_int, NULL);
	
/* 	sa_quit.sa_handler = SIG_IGN;
	//sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL); */

	//printf("g_signal_stat: %d\n", g_signal_stat);
	//printf("all_data->exit_stat: %d\n", all_data->exit_stat);
	//t_env	*qmark;
	//qmark = find_envvar(*all_data->env_list, "?");
	//printf("qmark->key:%s, qmark->val:%s\n", qmark->key, qmark->val);
	char	*ex_stat;
	if (g_signal_stat > 100)
	{
		all_data->exit_stat = g_signal_stat;
		ex_stat = ft_itoa(all_data->exit_stat);
		add_envvar(all_data->env_list, "?", ex_stat);
		free(ex_stat);
		//printf("g_signal_stat: %d\n", g_signal_stat);
		//printf("all_data->exit_stat: %d\n", all_data->exit_stat);
		//printf("qmark->key:%s, qmark->val:%s\n", qmark->key, qmark->val);
	}	
}

