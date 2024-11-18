/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:32:30 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 19:06:09 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		*ptr = c;
		ptr++;
		n--;
	}
	return (s);
}

/*
memset() function fills the first n bytes of the memory area pointed to 
by s with the constant byte c
*/

/*
#include <stdio.h> //puts, printf
#include <string.h> //memchr,memcmp,memcpy,memmove,memset
					//strchr,strcpy,strlen

int	main (void) {
	char str[] = "This is a ft_memset test.";
	printf("Test sentence: %s\n", str);

	memset(str,'$',9);
	printf("memset: %s\n", str);

	ft_memset(str,'<',6);
	printf("ft_memset: %s\n", str);

	return(0);
}
*/
