#include "signals.h"

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
	write(STDERR_FILENO, "\nrh-shell>", 10);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// Do nothing for ctrl-\ in interactive mode
}

void	setup_signals(void)
{
	disable_ctrl_char_echo();
	signal(SIGINT, handle_sigint);   // Handle ctrl-C
	signal(SIGQUIT, handle_sigquit); // Handle ctrl-\
	// ctrl-D (EOF) is handled by readline in the main loop
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
