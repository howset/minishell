/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:04:29 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/03 18:59:55 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*pdest;
	char	*psrc;

	if (!dest && !src)
		return (dest);
	if (dest < src)
		dest = ft_memcpy(dest, src, n);
	else
	{
		pdest = (char *)dest;
		psrc = (char *)src;
		while (n > 0)
		{
			n--;
			pdest[n] = psrc[n];
		}
	}
	return (dest);
}

/*
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*pdest;
	char	*psrc;

	pdest = (char *) dest;
	psrc = (char *) src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n > 0)
		{
			pdest[n] = psrc[n];
			n--;
		}
	}
	return (dest);
}
!! Failed warmachine
!! Failed libftunittest
*/

/*
memmove()  function  copies n bytes from memory area src to memory area dest.
The memory areas may overlap: copying takes place as though the bytes in src
are first copied into a temporary  array that does not overlap src or dest,
and the bytes are then copied from the temporary array to dest.
*/

/*
#include <stdio.h> //puts, printf
#include <string.h> //memchr,memcmp,memcpy,memmove,memset
					//strchr,strcpy,strlen

int	main(void)
{
	char str1[] = "memmove_1";
	char str2[] = "memmove_2";

	printf("\nstr1 before memmove: ", str1);

	// Copies contents of str2 to str1
	memmove(str1, str2, sizeof(str2));
	
	printf("\nstr1 after memmove: ", str1);

	char str3[] = "ft_memmove_1";
	char str4[] = "ft_memmove_2";

	printf("\nstr3 before ft_memmove: ", str3);

	// Copies contents of str2 to str1
	ft_memmove(str3, str4, sizeof(str4));
	
	printf("\nstr3 after ft_memmove: ", str3);
	
	return (0);
}
*/
