/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:34:55 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 19:05:30 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && size > (j + i + 1))
	{
		dst[j + i] = src[j];
		j++;
	}
	if (i < size)
		dst[j + i] = '\0';
	return (ft_strlen(src) + i);
}

/*
catenate the input string into a destination string.
If the destination buffer, limited by its size, isn't large 
enough to hold the copy, the  resulting string is truncated 
(but it is guaranteed to be null-terminated).  They return
the length of the total string they tried to create.
*/

/*
#include <stdio.h>
#include <bsd/string.h> //strlcat,strlcpy,strnstr
//cc -Wall -Werror -Wextra ft_strlen.c ft_strlcat.c -lbsd
int main(void)
{
	char dest[30] = "d1_123456";
	char src[30] = "Slim Shady";
	char dest2[30] = "d2_123456";
	char src2[30] = "Slim Shady";
	int r;
	int	size = 7;

	printf("Dest before ft_strlcat: %s\n", dest);
	r = ft_strlcat(dest,src,size);
	printf("Value returned: %d\n",r);
	printf("Dest after ft_strlcat: %s\n", dest);

	printf("\nDest before strlcat: %s\n", dest2);
	r = strlcat(dest2,src2,size);
	printf("Value returned: %d\n",r);
	printf("Dest after strlcat: %s\n", dest2);

	return(0);
}
*/
