/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:25:13 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 01:28:47 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

/*
 * rh_pwd() - Print Working Directory command implementation
 *
 * Return values:
 *   EXIT_SUCCESS (0): Successfully printed current directory
 *   EXIT_FAILURE (1): Failed to retrieve current directory
 *
 * Function flow:
 * 1. Get current working directory:
 *    - Uses getcwd() with NULL buffer for automatic allocation
 *    - Size 0 lets system determine required buffer size
 *
 * 2. Error handling:
 *    - If getcwd() returns NULL (error case):
 *       - Prints error message
 *       - Returns EXIT_FAILURE
 *
 * 3. Success path:
 *    - Prints current directory path
 *    - Frees allocated memory
 *    - Returns EXIT_SUCCESS
 *
 * Note:
 *   - Automatically handles memory allocation/deallocation
 *   - Thread-safe implementation
 *   - Uses ft_printf for output handling
*/

int	rh_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf("pwd: error retrieving current directory \n");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

/*
 * rh_cd() - Change Directory command implementation
 *
 * Parameters:
 *   path: Target directory path (can be NULL)
 *
 * Return values:
 *   EXIT_SUCCESS (0): Successfully changed directory
 *   EXIT_FAILURE (1): Failed to change directory
 *
 * Function flow:
 * 1. Handle NULL path (cd with no arguments):
 *    - Attempt to get HOME environment variable
 *    - Return failure if HOME not set
 *    - Use HOME as target path
 *
 * 2. Change directory:
 *    - Use chdir() to change current working directory
 *    - Handle errors if directory doesn't exist
 *
 * Example usage:
 *   rh_cd("/usr/local")     -> changes to /usr/local
 *   rh_cd(NULL)             -> changes to HOME directory
 *   rh_cd("invalid_path")   -> returns error
*/

int	rh_cd(char *path)
{
	char	*home;

	if (!path)
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		path = home;
	}
	if (chdir(path) != 0)
	{
		ft_fprintf(STDERR_FILENO, " No such file or directory\n", path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
