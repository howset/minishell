#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

// utils.c
void	*malloc_perex(size_t bytes, char *msg);

// ft_fprintf.c
int		ft_fprintf(int fd, const char *fmt, ...);

#endif