/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pathfinding_build.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:55:26 by hsetya            #+#    #+#             */
/*   Updated: 2025/01/19 01:55:27 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/**This function iterates over the directoriess in PATH (separated by :)and
 * tries to find the command in each of them (by means of `build_fullpath`
 * and then verification by `access`). If the command is found, it returns the
 * full path to the command.
 * 		Takes PATH, the command, the full_path and the length of the path.
 * 		Returns the full path to the command if it is found, otherwise NULL.
 */
char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len)
{
	char	*start;
	char	*end;
	char	*result;

	start = path;
	end = ft_strchr(start, ':');
	while (end || (*start != '\0'))
	{
		if (end)
			*end = '\0';
		result = try_access(full_path, start, cmd, path_len);
		if (result)
			return (full_path);
		if (end)
			start = end + 1;
		else
			break ;
		end = ft_strchr(start, ':');
	}
	return (NULL);
}

/**
 * @brief Tries to build a valid executable path and checks its accessibility.
 *
 * This function attempts to construct a full path for an executable by
 * combining the provided directory path and command name. After building
 * the path, it verifies if the file is accessible for execution (X_OK
 * permission).
 *
 * @param full_path A pointer to a buffer where the full path will be stored.
 * @param start A pointer to the beginning of the directory path segment.
 * @param cmd A pointer to the command (executable name) to append.
 * @param path_len The length of the buffer allocated for the full path.
 *
 * @return A pointer to the built path if it is executable, otherwise NULL.
 */
char	*try_access(char *full_path, char *start, char *cmd, size_t path_len)
{
	char	*result;

	result = build_fullpath(full_path, start, cmd, path_len);
	if (result && access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}

/**This function builds (puts together) the dirs leading to the command
 * 		Takes the full_path, the dir, the cmd, and the length of the path.
 * 		Returns the directories leading to the command.
 */
char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len)
{
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	if (dir_len + cmd_len + 2 > path_len)
		return (NULL);
	ft_strlcpy(full_path, dir, path_len);
	if (full_path[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		ft_strlcpy(full_path + dir_len + 1, cmd, path_len - dir_len - 1);
	}
	else
		ft_strlcpy(full_path + dir_len, cmd, path_len - dir_len);
	return (full_path);
}
