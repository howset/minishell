/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pathfinding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:45 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 01:55:11 by hsetya           ###   ########.fr       */
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
	size_t	path_len;
	char	*full_path;
	char	*path;

	full_path = resolve_path(cmd, env_list, &path_len);
	if (!full_path)
		return (NULL);
	path = find_envvar(env_list, "PATH")->val;
	return (process_dirs(path, cmd, full_path, path_len));
}

/**
 * resolve_path - Handles the command path resolution.
 *
 * This function checks if the given command contains a '/' character. If it
 * does, it treats the command as a direct path and performs the following
 * checks:
 * - If the path exists and is a directory, it prints an error message and
 *   exits with code 126.
 * - If the path exists and is executable, it returns a duplicate of the
 *   command.
 * - If the path exists but is not executable, it prints a permission denied
 *   message and exits with code 126.
 * - If the path does not exist, it prints a no such file or directory message
 *   and exits with code 127.
 *
 * If the command does not contain a '/', it initializes the full path using
 * the environment list.
 *
 * @param cmd The command to be executed.
 * @param env_list The environment list to be used for path initialization.
 * @param path_len A pointer to a size_t variable to store the length of the
 * path.
 * @return A pointer to the full path of the command, or NULL if an error
 * occurs.
 */
char	*resolve_path(char *cmd, t_env *env_list, size_t *path_len)
{
	struct stat	st;
	char		*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				ft_fprintf(STDERR_FILENO, "%s: is a directory\n", cmd);
				exit(126);
			}
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			else
			{
				ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", cmd);
				exit(126);
			}
		}
		ft_fprintf(STDERR_FILENO, "%s: No such file or directory\n", cmd);
		exit(127);
	}
	full_path = init_fullpath(env_list, path_len);
	return (full_path);
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
