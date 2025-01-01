/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pathfinding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:45 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/01 19:31:10 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/**This function looks now a bit weird because it is now forced to be divided
 * into several parts to meet the norm reqs, but somehow ended up a bit more
 * digestible. First, the initialization of full_path by malloc, then find
 * PATH in env_list via find_envvar and store it in path. Then `process_dirs`
 * "builds" the complete path of the cmd.
 * 		Takes a cmd (e.g. ls, or cat) and the env_list that contains PATH
 * 		Returns the complete path to the command (e.g. /dir/dir/cmd)
 */
char	*find_path(char *cmd, t_env *env_list)
{
	struct stat	st;
	size_t		path_len;
	char		*path;
	char		*full_path;

	// If user typed a path (contains '/'),
	//	check if it’s a directory or executable
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
				return (NULL); // "Is a directory"
			// If it’s not a directory, check execute permission
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd)); // replace with your own strdup
		}
		return (NULL); // "command not found"
	}
	// Otherwise, proceed with existing PATH search
	full_path = init_fullpath(env_list, &path_len);
	if (!full_path)
		return (NULL);
	path = find_envvar(env_list, "PATH")->val;
	return (process_dirs(path, cmd, full_path, path_len));
}

/**This function basically initializes (malloc) full_path.
 * 		Takes the env_list, and the length of the path
 * 		Returns malloc'ed full_path.
 */
char	*init_fullpath(t_env *env_list, size_t *path_len)
{
	t_env	*node;
	char	*path;
	char	*full_path;

	node = find_envvar(env_list, "PATH");
	if (!node || !node->val)
		return (NULL);
	path = node->val;
	*path_len = ft_strlen(path);
	full_path = malloc_perex(*path_len, "Malloc error on full_path");
	if (!full_path)
		return (NULL);
	return (full_path);
}

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
	while ((end = ft_strchr(start, ':')) || (*start != '\0'))
	{
		if (end)
			*end = '\0';
		result = build_fullpath(full_path, start, cmd, path_len);
		if (result && access(full_path, X_OK) == 0)
		{
			if (end)
				*end = ':';
			return (full_path);
		}
		if (end)
			*end = ':';
		if (!end)
			break ;
		start = end + 1;
	}
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
