/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:44:32 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/15 13:57:37 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (size > 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	res = malloc(nmemb * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, nmemb * size);
	return (res);
}

/*
The calloc() function allocates memory for an array of nmemb 
elements of size bytes each  and returns  a  pointer to the 
allocated memory.  The memory is set to zero.

# setting nmemb and size to 1 may have other solutions like this:
if (nmemb && size && nmemb > (UINT_MAX / size))
		return (NULL);
//UINT_MAX in #include <limits.h>
*/

/*
#include <stdio.h>
int main() 
{
	int *res;
	int size = 5; //0 to fail

	res = (int *)ft_calloc(0,(size * sizeof(int))); //nmemb 0 to fail
	if (res == NULL) printf("ft_calloc failed.\n");
	else printf("ft_calloc success.\n");

	free(res);
	return 0;
}
*/
