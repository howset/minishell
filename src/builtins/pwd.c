/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:25:13 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/15 15:08:31 by hsetyamu         ###   ########.fr       */
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
