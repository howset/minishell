/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 23:10:20 by reldahli         ###   ########.fr       */
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
void	handle_sigint(void)
{
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	add_envvar(g_env, "?", "130");
}

/**
 * CTRL + \
 * ??? where to put???
 */
/*
	// if (signum)
	// 	ft_fprintf(STDERR_FILENO, "(fake core dumped)\n");
	// else
	// 	ft_fprintf(STDERR_FILENO, "what error?\n");
*/
void	handle_sigquit(void)
{
	rl_point = rl_end;
	rl_redisplay();
}

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		handle_sigint();
	}
	else if (signum == SIGQUIT)
	{
		handle_sigquit();
	}
	add_envvar(g_env, "?", "130");
}
/**
 * CTRL + D (EOF) is handled by readline in the main loop
 * CTRL + C SIGINT
 * CTRL + \ SIGQUIT
 * SA_RESTART | SA_SIGINFO;
	// Restart interrupted syscalls | SA_SIGINFO to pass extra info
 */
/*
	// sa_int.sa_sigaction = handle_sigint;
*/

void	setup_signals(t_env **env)
{
	struct sigaction	sa;

	g_env = env;
	sa.sa_handler = handle_signals;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	disable_echoctl();
}
