/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/18 20:16:45 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		res = ft_split(input, ' '); //delimiter is just a space
		i = 0;
		while (res[i]) 
		{
			printf("Word %d: %s\n", i + 1, res[i]);
			free(res[i]);
			i++;
		}
		free(input);
	}
	return 0;
}