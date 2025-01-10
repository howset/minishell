/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:55:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/10 18:16:52 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void setup_signals(void) {
	struct sigaction sa;

	// Handle SIGINT (Ctrl-C)
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // Restart interrupted syscalls
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	// Handle SIGQUIT (Ctrl-\)
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void handle_sigint(int signo) {
	(void)signo;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void handle_sigquit(int signo) {
	(void)signo; // Suppress unused parameter warning
	// Ignore Ctrl-\ (SIGQUIT)
	write(STDOUT_FILENO, "Quit (ignored)\n", 15);
}