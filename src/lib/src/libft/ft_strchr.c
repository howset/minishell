/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:12:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/03 16:25:01 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}

/*
char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s != '\0')
		s++;
	if (*s == c)
		return ((char *) s);
	else
		return (NULL);
}
!! Failed libftTester
!! Failed fsoares
*/

/*
returns  a pointer to the first occurrence of the character c in the
string s
*/

/*
#include <stdio.h>
#include <string.h> //memchr,memcmp,memcpy,memmove,memset
					//strchr,strcpy,strlen
int	main(void)
{
	char	*s = "Test sentence";

	printf("strchr: %p\n", strchr(s, 't'));
	printf("ft_strchr: %p\n", ft_strchr(s, 't'));

	printf("strchr: %p\n", strchr(s, 'b'));
    printf("ft_strchr: %p\n", ft_strchr(s, 'b'));	
	
	printf("strchr: %p\n", strchr(s, '\0'));
    printf("ft_strchr: %p\n", ft_strchr(s, '\0'));
    
    printf("strchr: %p\n", strchr(s, 't' + 256)); // tester
    printf("ft_strchr: %p\n", ft_strchr(s, 't' + 256));

}
*/
