/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:57:18 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/17 19:25:45 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

/**
 * colorize_prompt - Generates a colorized prompt string.
 * @wdir: The current working directory to be included in the prompt.
 *
 * This function creates a colorized prompt string by combining
 * predefined color codes and the provided working directory.
 * The resulting prompt string is dynamically allocated and should
 * be freed by the caller to avoid memory leaks.
 *
 * The color scheme used is:
 * - "rh-shell> " in yellow and bold.
 * - The working directory in blue and bold.
 * - The reset color code to revert to default terminal colors.
 *
 * Returns: A pointer to the dynamically allocated colorized prompt string.
 */
char	*colorize_prompt(char *wdir)
{
	char *temp;
	char *temp1;
	char *temp2;
	char *col_prompt;

	temp = ft_strjoin(YEL BOLD, "rh-shell> ");
	temp1 = ft_strjoin(BLU BOLD, wdir);
	temp2 = ft_strjoin(temp1, RES);
	col_prompt = ft_strjoin(temp, temp2);
	free(temp);
	free(temp1);
	free(temp2);
	return (col_prompt);
}

/**
 * fancy_prompt - Generates a fancy shell prompt string.
 *
 * This function retrieves the current working directory, applies colorization
 * to it, and then constructs a prompt string that includes the colorized
 * working directory followed by a newline and the prompt symbol "$> ".
 *
 * Return: A dynamically allocated string containing the fancy prompt.
 *         The caller is responsible for freeing the returned string.
 */
char	*fancy_prompt(void)
{
	char *wdir;
	char *col_prompt;
	char *prompt;

	wdir = getcwd(NULL, 0);
	col_prompt = colorize_prompt(wdir);
	prompt = ft_strjoin(col_prompt, "\n$> ");
	free(wdir);
	free(col_prompt);
	return (prompt);
}

/**
 * This function is the prompt for the shell. It uses the readline function
 * from the readline library to get the input from the user. It also adds the
 * input to the history list.
 * 		Takes the declared char *input from main.
 * 		Returns the input string.
 * 		if (!input) // Handle ctrl-D (EOF)
 */
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
		add_history(input);
	free(prompt);
	return (input);
}
