/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:40:54 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/03 15:00:33 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*pdest;
	char	*psrc;

	pdest = (char *) dest;
	psrc = (char *) src;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*pdest = *psrc;
		pdest++;
		psrc++;
		n--;
	}
	return (dest);
}

/*
memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap. Use memmove if the memory areas overlap.
*/

/*
#include <stdio.h>
#include <string.h> //memchr,memcmp,memcpy,memmove,memset
					//strchr,strcpy,strlen

int	main(void)
{
	char str1[] = "memcpy_1";
	char str2[] = "memcpy_2";

	printf("\nstr1 before memcpy: %s", str1);
	
	// Copies contents of str2 to str1
	memcpy(str1, str2, sizeof(str2));

	printf("\nstr1 after memcpy: %s", str1);
	
	char str3[] = "ft_memcpy_1";
	char str4[] = "ft_memcpy_2";

	printf("\nstr1 before ft_memcpy: %s", str3);

	// Copies contents of str2 to str1
	ft_memcpy(str3, str4, sizeof(str4));

	printf("\nstr1 before ft_memcpy: %s", str3);

	return 0;
}
*/
