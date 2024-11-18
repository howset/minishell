/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:04:09 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:52:47 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getwcount(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (count);
}

static size_t	ft_getwlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	ft_freearr(char **arr, size_t i)
{
	while (i > 0)
	{
		i--;
		free(*(arr + i));
	}
	free(arr);
}

static char	**realsplit(char const *s, char c, char **arr, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(arr + i) = ft_substr(s, j, ft_getwlen(&*(s + j), c));
		if (!*(arr + i))
		{
			ft_freearr(arr, i);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(arr + i) = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	wordcount;

	if (!s)
		return (NULL);
	wordcount = ft_getwcount(s, c);
	array = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	array = realsplit(s, c, array, wordcount);
	return (array);
}

/*
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/
/*
#include <stdio.h>

void printRes(char const *s, char c) 
{
    char	**res;
    int		i;
    
    res = ft_split(s, c);
    if (res) 
    {
        i = 0;
        while (res[i]) 
        {
            printf("Word %d: %s\n", i + 1, res[i]);
            free(res[i]); //free individual strings
            i++;
        }
        free(res); //free array
    }
}

int main(void)
{
	//char test[] = "This is a test";
    //printRes(test, ' ');
	
	//const char *test = "Dog,Dogdog,Cat,Catcat";
	//printRes(test, ',');
	
	//const char *test = "Dog,Dogdog,Cat,Catcat";
	//printRes(test, ' ');

	const char *test = "123-4567-89-0";
	printRes(test, '-');
	//size_t cwords;
	//cwords = ft_getwcount(test, '-');
	//printf("cwords:%ld",cwords);
	//size_t wlen;
	//wlen = ft_getwlen(test,' ');
	//printf("wlen:%ld",wlen);
}
*/
