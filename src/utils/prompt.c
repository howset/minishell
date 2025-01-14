/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:46:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_prompt_base(void)
{
	char	*base;

	base = ft_strjoin(YEL BOLD, "rh-shell> ");
	return (base);
}

char	*create_prompt_dir(char *wdir)
{
	char	*dir;
	char	*temp;

	temp = ft_strjoin(BLU BOLD, wdir);
	dir = ft_strjoin(temp, RES);
	free(temp);
	return (dir);
}

char	*create_prompt_final(char *base, char *dir)
{
	char	*temp;
	char	*prompt;

	temp = ft_strjoin(base, dir);
	prompt = ft_strjoin(temp, "\n$> ");
	free(temp);
	return (prompt);
}

char	*fancy_prompt(void)
{
	char	*wdir;
	char	*base;
	char	*dir;
	char	*prompt;

	wdir = getcwd(NULL, 0);
	base = create_prompt_base();
	dir = create_prompt_dir(wdir);
	prompt = create_prompt_final(base, dir);
	free(wdir);
	free(base);
	free(dir);
	return (prompt);
}

char	*prompt_hist(char *input)
{
	char	*prompt;

	prompt = fancy_prompt();
	input = readline(prompt);
	if (!input)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(input) > 0)
	{
		add_history(input);
	}
	free(prompt);
	return (input);
}
