/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:27:28 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/03 14:43:56 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
/*
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}
*/

/*
returns a pointer to the last occurrence of the character c in the
string s.
*/

/*
#include <stdio.h>
#include <string.h> //memchr,memcmp,memcpy,memmove,memset
					//strchr,strcpy,strlen
int	main(void)
{
	char	*s = "Test sentence";

	printf("strrchr: %p\n", strrchr(s, 'n'));
	printf("ft_strrchr: %p\n", ft_strrchr(s, 'n'));

	printf("strrchr: %p\n", strrchr(s, 'b'));
    printf("ft_strrchr: %p\n", ft_strrchr(s, 'b'));	
	
	printf("strrchr: %p\n", strrchr(s, '\0'));
    printf("ft_strrchr: %p\n", ft_strrchr(s, '\0'));
    
    printf("strrchr: %p\n", strrchr(s, 't' + 256)); // tester
    printf("ft_strrchr: %p\n", ft_strrchr(s, 't' + 256));

}
*/
