/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pathfinding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:45 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	check_directory(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_fprintf(STDERR_FILENO, "%s: is a directory\n", cmd);
		exit(126);
	}
	return (0);
}

int	check_executable(char *cmd)
{
	if (access(cmd, X_OK) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", cmd);
		exit(126);
	}
	return (0);
}

char	*handle_absolute_path(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: No such file or directory\n", cmd);
		exit(127);
	}
	check_directory(cmd);
	check_executable(cmd);
	return (ft_strdup(cmd));
}

char	*handle_path_search(char *cmd, t_env *env_list)
{
	size_t	path_len;
	char	*path;
	char	*full_path;

	full_path = init_fullpath(env_list, &path_len);
	if (!full_path)
	{
		return (NULL);
	}
	path = find_envvar(env_list, "PATH")->val;
	return (process_dirs(path, cmd, full_path, path_len));
}

char	*find_path(char *cmd, t_env *env_list)
{
	if (ft_strchr(cmd, '/'))
	{
		return (handle_absolute_path(cmd));
	}
	return (handle_path_search(cmd, env_list));
}

char	*init_fullpath(t_env *env_list, size_t *path_len)
{
	t_env	*node;
	char	*path;
	char	*full_path;

	node = find_envvar(env_list, "PATH");
	if (!node || !node->val)
	{
		return (NULL);
	}
	path = node->val;
	*path_len = ft_strlen(path);
	full_path = malloc_perex(*path_len, "Malloc error on full_path");
	if (!full_path)
	{
		return (NULL);
	}
	return (full_path);
}

char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len)
{
	char	*start;
	char	*end;
	char	*result;

	start = path;
	while ((end = ft_strchr(start, ':')) || (*start != '\0'))
	{
		if (end)
		{
			*end = '\0';
		}
		result = build_fullpath(full_path, start, cmd, path_len);
		if (result && access(full_path, X_OK) == 0)
		{
			if (end)
			{
				*end = ':';
			}
			return (full_path);
		}
		if (end)
		{
			*end = ':';
		}
		if (!end)
		{
			break ;
		}
		start = end + 1;
	}
	return (NULL);
}

char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len)
{
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	if (dir_len + cmd_len + 2 > path_len)
	{
		return (NULL);
	}
	ft_strlcpy(full_path, dir, path_len);
	if (full_path[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		ft_strlcpy(full_path + dir_len + 1, cmd, path_len - dir_len - 1);
	}
	else
	{
		ft_strlcpy(full_path + dir_len, cmd, path_len - dir_len);
	}
	return (full_path);
}
