/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:45:39 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 19:03:25 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;

	len = ft_strlen(s) + 1;
	res = malloc(sizeof(char) * len);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s, len);
	return (res);
}

/*
returns a pointer to a new string which is a duplicate of the string s.
Memory for the new string is obtained with malloc.
*/

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char	*src;
	const char	*src2;
	char	*res;
	char	*res2;

	src = "Test sentence1"; //length: 14 chars
	src2 = "Test sentence2";
	res = ft_strdup(src);

	printf("Res ft_strdup: %s\n", res);

	res2 = strdup(src2);

	printf("Res strdup: %s\n", res2);
	
	free(res);
	free(res2);
	return 0;
}
*/
