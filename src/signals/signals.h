#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"

void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	reset_signals(void);

#endif
