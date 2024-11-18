/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:47:05 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/19 19:37:46 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *stock);
char	*extract_line(char *stock);
char	*clean_up(char *stock);

char	*get_next_line(int fd)
{
	char		*extracted;
	static char	*stock[1024] = {NULL};
	char		*remains;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
	{
		if (stock[fd] != NULL)
			free(stock[fd]);
		return (NULL);
	}
	stock[fd] = read_line(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	extracted = extract_line(stock[fd]);
	remains = clean_up(stock[fd]);
	stock[fd] = remains;
	return (extracted);
}

char	*read_line(int fd, char *stock)
{
	int		bytes;
	char	*line_fr_read;

	if (!stock)
		stock = null_malloc(1, sizeof(char));
	line_fr_read = null_malloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line_fr_read)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stock, '\n') && bytes != 0)
	{
		bytes = read(fd, line_fr_read, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(stock);
			free(line_fr_read);
			return (NULL);
		}
		line_fr_read[bytes] = '\0';
		stock = freebuf_join(stock, line_fr_read);
	}
	free(line_fr_read);
	return (stock);
}

char	*extract_line(char *stock)
{
	size_t	i;
	char	*extracted;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] != '\n' && stock[i])
		i++;
	extracted = null_malloc(i + 2, sizeof(char));
	if (!extracted)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		extracted[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
	{
		extracted[i] = stock[i];
		i++;
	}
	extracted[i] = '\0';
	return (extracted);
}

char	*clean_up(char *stock)
{
	int		i;
	int		j;
	char	*remains;

	i = 0;
	while (stock[i] != '\0' && stock[i] != '\n')
		i++;
	if (stock[i] == '\0')
	{
		free(stock);
		return (NULL);
	}
	remains = null_malloc(ft_strlen(stock) - i + 1, sizeof(char));
	if (!remains)
	{
		free(stock);
		return (NULL);
	}
	i++;
	j = 0;
	while (stock[i] != '\0')
		remains[j++] = stock[i++];
	remains[j] = '\0';
	free(stock);
	return (remains);
}

/*
#include <stdio.h>

int main(void)
{
    int fd1;
    int fd2;
    char *line;
    int	lines;
	char file1[] = "./txts/lorem1.txt";
	char file2[] = "./txts/lorem2.txt";

    fd1 = open(file1, O_RDONLY);
    fd2 = open(file2, O_RDONLY);
    lines = 1;
    printf("\n >> Reading from %s:\n", file1);
    while ((line = get_next_line(fd1)))
        printf("%d ->%s\n", lines++, line);
    free(line);
    lines = 1;
    printf("\n >> Reading from %s:\n", file2);
    while ((line = get_next_line(fd2)))
        printf("%d ->%s\n", lines++, line);
    free(line);
    close(fd1);
    close(fd2);
    return (0);
}
*/
