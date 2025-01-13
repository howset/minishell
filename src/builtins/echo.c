/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:34:28 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 01:16:37 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

/*
 * This function implements a basic 'echo' command similar to the shell built-in:
 * 1. Takes an array of string arguments (char *args[])
 * 2. Has support for the '-n' option which suppresses the trailing newline
 * 3. Works as follows:
 *	- First loops through arguments to check for '-n' option flags
 *	- Then prints all remaining arguments with spaces between them
 *	- Adds newline at the end unless '-n' option was specified
 */

int	rh_echo(char *args[])
{
	int	i;
	int	opt;
	int	first_arg;

	opt = 0;
	i = 1;
	while (args[i] && check_n(args[i]))
	{
		opt = 1;
		i++;
	}
	first_arg = 1;
	while (args[i])
	{
		if (!first_arg)
			writing(" ");
		writing(args[i]);
		first_arg = 0;
		i++;
	}
	if (!opt)
		return (writing("\n"));
	return (EXIT_SUCCESS);
}
/*
 * This function:
 * 1.Takes a string argument arg
 * 2.Returns 1 if the argument is in the format -nnn...
 *	(one or more 'n' characters after a hyphen)
 * 3.Returns 0 in all other cases:
 *	- If arg is NULL
 *	- If arg doesn't start with -
 *	- If any character after the - is not 'n'
 */

int	check_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
/*
 * Function flow:
 * 1. Attempts to write string to stdout using write()
 * 2. write() parameters:
 *	- STDOUT_FILENO: File descriptor for standard output
 *	- str: String buffer to write
 *	- ft_strlen(str): Number of bytes to write
 * 3. If write() returns -1 (error):
 *	- Prints error message using perror()
 *	- Returns EXIT_FAILURE
 * 4. SOtherwise returns EXIT_SUCCES
 */

int	writing(char *str)
{
	if (write(STDOUT_FILENO, str, ft_strlen(str)) == -1)
	{
		perror("echo: write error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
