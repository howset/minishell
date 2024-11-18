/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/18 20:32:56 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	find_delimiter(char *input)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(input);
	while (i <= len)
	{
		if (input[i] == ' ' || input[i] == ',' || input[i] == '.')
			return(input[i]);
		i++;
	}
	return(input[i]);
}

int main()
{
	char*	input;
	char	**res;
	int		i;
	
	while (1)
	{	
		input = readline("wtf-shell> "); //display prompt
		add_history(input); //add input to readline history
		if (ft_strncmp(input,"exit", 4) == 0) //exit
			exit(0);
		res = ft_split(input, find_delimiter(input)); //delimiter is space, komma, or period
		i = 0;
		while (res[i]) 
		{
			ft_printf("Word %d: %s\n", i + 1, res[i]);
			free(res[i]);
			i++;
		}
		free(input);
	}
	return 0;
}