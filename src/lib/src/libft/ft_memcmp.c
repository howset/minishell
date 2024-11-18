/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:18:10 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 19:04:47 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (i < n)
	{
		if (*((unsigned char *)s1 + i) != *((unsigned char *)s2 + i))
		{
			res = (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
			return (res);
		}
		++i;
	}
	return (0);
}

/*
compares the first n bytes (each interpreted as unsigned char) 
of the memory areas s1 and s2
returns an integer less than, equal to, or greater  than  zero  
if  the first n bytes of s1 is found, respectively, 
to be less than, to match, or be greater than the first n bytes
of s2
*/

/*
#include <stdio.h>
#include <string.h> //memchr,memcmp,memcpy,memmove,memset
					//strchr,strcpy,strlen

int main(void)
{
	int	res;
	//char *s1 = "TEST";
	//char *s2 = "test";
	char *s1 = "whatnow";
	char *s2 = "whatnownow";

	res = ft_memcmp(s1, s2, 100);
	printf("Res ft: %d\n", res);
	res = memcmp(s1, s2, 100);
	printf("Res rf: %d\n", res);
}
*/
