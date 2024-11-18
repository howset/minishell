/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:38:29 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 16:32:12 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (big[i] == little[j] && big[i] && i < len)
		{
			i++;
			j++;
		}
		if (!little[j])
			return ((char *)&big[i - j]);
		i = (i - j) + 1;
	}
	return (NULL);
}

/*
locates the first occurrence of the  null-terminated string little
in the string big, where not more than len characters are searched
*/

/*
#include <stdio.h>
#include <bsd/string.h> //strlcat,strlcpy,strnstr

int	main(void)
{
	const char *largestring = "Foo Bar Baz";
	const char *smallstring = "Bar";
	int n = 6;
	char *ptr;
	char *ptr2;

	ptr = strnstr(largestring, smallstring, n);
	printf("strnstr: %s\n",ptr);
	ptr2 = ft_strnstr(largestring, smallstring, n);
	printf("ft_strnstr: %s\n", ptr2);
}
*/
