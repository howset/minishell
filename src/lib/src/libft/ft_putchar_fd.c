/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:06:51 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:54:37 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* write c to file descriptor*/
/*
int main(void) {
    
	ft_putchar_fd('H', 0); // STDIN
	ft_putchar_fd('H', 1); // STDOUT
	ft_putchar_fd('H', 2); // STDERR

	return 0;
}
*/
