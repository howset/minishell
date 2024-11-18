/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:33:27 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 16:30:19 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (i < (n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
compares the two strings s1 and s2
•  0, if the s1 and s2 are equal;
•  a negative value if s1 is less than s2;
•  a positive value if s1 is greater than s2.
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
	char *s1 = "wBatnow";
	char *s2 = "whatnow";

	res = ft_strncmp(s1, s2, 4);
	printf("Res ft: %d\n", res);
	res = strncmp(s1, s2, 4);
	printf("Res rf: %d\n", res);
}
*/
