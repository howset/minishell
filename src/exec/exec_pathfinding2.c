/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pathfinding2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:23:15 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:37:02 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/* ... add header ... */

char	*try_path(char *full_path, char *start, char *cmd, size_t path_len)
{
	char	*result;

	result = build_fullpath(full_path, start, cmd, path_len);
	if (result && access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}

void	handle_path_segment(char **end, char c)
{
	if (*end)
		**end = c;
}

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
		result = try_path(full_path, start, cmd, path_len);
		if (result)
		{
			handle_path_segment(&end, ':');
			return (full_path);
		}
		handle_path_segment(&end, ':');
		if (!end)
			break ;
		start = end + 1;
		end = ft_strchr(start, ':');
	}
	return (NULL);
}

void	copy_path_components(char *full_path, char *dir, char *cmd,
							size_t path_len)
{
	size_t	dir_len;

	dir_len = ft_strlen(dir);
	ft_strlcpy(full_path, dir, path_len);
	if (full_path[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		ft_strlcpy(full_path + dir_len + 1, cmd, path_len - dir_len - 1);
	}
	else
		ft_strlcpy(full_path + dir_len, cmd, path_len - dir_len);
}

char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len)
{
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	if (dir_len + cmd_len + 2 > path_len)
		return (NULL);
	copy_path_components(full_path, dir, cmd, path_len);
	return (full_path);
}
