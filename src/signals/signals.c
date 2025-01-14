/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 19:50:50 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

t_env	**g_env;

/**
 * heredoc must accepts ctrl+c but not ctrl+\
 * sleep accepts both, but ctrl+c does not immediately change echo $?
 * 						ctrl+| should dump core
 */

/**
 * CTRL + C
*/
void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	add_envvar(g_env, "?", "130");
}

/**
 * CTRL + \
 * ??? where to put???
*/
 void	handle_sigquit(int signum)
{
	ft_fprintf(STDERR_FILENO, "Quit: ");
	if (signum)
		ft_fprintf(STDERR_FILENO, "(fake core dumped)\n");
	else
		ft_fprintf(STDERR_FILENO, "what error?\n");
	add_envvar(g_env, "?", "131");
}

/**
 * CTRL + D (EOF) is handled by readline in the main loop
 * CTRL + C SIGINT
 * CTRL + \ SIGQUIT
 * SA_RESTART | SA_SIGINFO; // Restart interrupted syscalls | SA_SIGINFO to pass extra info
*/
void	setup_signals(t_env **env)
{
	struct sigaction sa;

	g_env = env;
	sa.sa_handler = handle_sigint;
	//sa_int.sa_sigaction = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

