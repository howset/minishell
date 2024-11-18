/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/18 17:42:04 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char* input;
	
	while (1)
	{	
		input = readline("wtf-shell> "); //display prompt
		add_history(input); //add input to readline history
		if (ft_strncmp(input,"exit", 4) == 0)
			exit(0);
		printf("input was:%s\n", input); //just a feedback (useful for echo??)
		free(input);
	}
	return 0;
}