/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:07:51 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:56:24 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
/*
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
*/

/* write string s to file descriptor with endline (\n)*/

/*
int main(void) {
    
	ft_putendl_fd("Test0", 0); // STDIN
	ft_putendl_fd("Test1", 1); // STDOUT
	ft_putendl_fd("Test2", 2); // STDERR

	return 0;
}
*/
