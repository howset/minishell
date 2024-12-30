/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:57:40 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/30 04:57:42 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

// utils.c
void	*malloc_perex(size_t bytes, char *msg);

// ft_fprintf.c
int		ft_fprintf(int fd, const char *fmt, ...);

#endif
