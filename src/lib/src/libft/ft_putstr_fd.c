/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:08:47 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:55:00 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
*/

/* write string s to file descriptor*/
/*
int main(void) {
    
	ft_putstr_fd("Test0", 0); // STDIN
	ft_putstr_fd("Test1", 1); // STDOUT
	ft_putstr_fd("Test2", 2); // STDERR

	return 0;
}
*/
