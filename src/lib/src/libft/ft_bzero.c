/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:24:18 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 19:05:12 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*
The  bzero()  function  erases the data in the n bytes of the 
memory starting at the location pointed to by s, 
by writing zeros (bytes containing '\0') to that area.
*/

/*
#include <stdio.h> //puts, printf
#include <string.h> //strcpy

int	main (void) {
	char str[] = "This is a ft_bzero test.";
	
	printf("Test sentence: %s\n", str);

	//memset(str,'$',9);
	//printf("memset: %s\n", str);

	//ft_memset(str,'<',6);
	//printf("ft_memset: %s\n", str);

	bzero(str,3);
	printf("bzero: %s\n", str);
	
	ft_bzero(str,3);
	printf("ft_bzero: %s\n", str);

	return(0);
}
*/
