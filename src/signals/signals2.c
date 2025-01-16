#include "signals.h"

// Global variable to indicate if we are in a blocking command
int g_blocking_command = 0;
t_env	**g_env;

// Signal handler for SIGINT (Ctrl-C)
void handle_sigint(void)
{
	if (g_blocking_command)
		write(1, "\n", 1);
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// Signal handler for SIGQUIT (Ctrl-\)
void handle_sigquit(void)
{
	if (g_blocking_command)
		write(1, "Quit: fake core dumped\n", 23);
}

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		handle_sigint();
		add_envvar(g_env, "?", "130");
	}
	else if (signum == SIGQUIT)
	{
		handle_sigquit();
		add_envvar(g_env, "?", "131");
	}
}

// Setup signal handlers
void setup_signals(t_env **envgit)
{
/* 	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL); */
	
	struct sigaction	sa;

	g_env = env;
	sa.sa_handler = handle_signals;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
