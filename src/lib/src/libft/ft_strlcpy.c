/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:34:42 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 19:04:19 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	res;

	res = 0;
	if (size == 0)
	{
		while (src[res])
			res++;
		return (res);
	}
	while (res < size -1 && src[res] != '\0')
	{
		dst[res] = src[res];
		res++;
	}
	if (res < size)
		dst[res] = '\0';
	while (src[res] != '\0')
		res++;
	return (res);
}

/*
copy the input string into a destination string.
If the destination buffer, limited by its size, isn't large 
enough to hold the copy, the  resulting string is truncated 
(but it is guaranteed to be null-terminated).  They return
the length of the total string they tried to create.
*/

/*
#include <stdio.h>
#include <bsd/string.h> //strlcat,strlcpy,strnstr

int	main(void)
{
	char	dst[20];
	char	dst2[20];
	const char	*src;
	const char	*src2;
	size_t	res;
	size_t	res2;

	src = "Test sentence1"; //length: 14 chars
	src2 = "Test sentence2";
	res = ft_strlcpy(dst, src, sizeof(dst));

	printf("Res ft_strlcpy: %zu\n Characters: %s\n", res, dst);

	res2 = strlcpy(dst2, src2, sizeof(dst2));

	printf("Res strlcpy: %zu\n Characters: %s\n", res2, dst2);
}
*/
