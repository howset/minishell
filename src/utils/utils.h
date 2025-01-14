/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:57:40 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

// utils.c
void	*malloc_perex(size_t bytes, char *msg);

// ft_fprintf.c
int		ft_fprintf(int fd, const char *fmt, ...);

// Prompt functions
char	*create_prompt_base(void);
char	*create_prompt_dir(char *wdir);
char	*create_prompt_final(char *base, char *dir);
char	*fancy_prompt(void);
char	*prompt_hist(char *input);

#endif
