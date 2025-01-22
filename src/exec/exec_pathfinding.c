/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pathfinding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:45 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:31:38 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/* ... existing header ... */

void	handle_direct_path(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: No such file or directory\n", cmd);
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_fprintf(STDERR_FILENO, "%s: is a directory\n", cmd);
		exit(126);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", cmd);
		exit(126);
	}
}

char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		handle_direct_path(cmd);
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*init_fullpath(t_env *env_list, size_t *path_len)
{
	t_env	*node;
	char	*path;
	char	*full_path;

	node = find_envvar(env_list, "PATH");
	if (!node)
		return (NULL);
	if (!node->val)
		return (NULL);
	path = node->val;
	*path_len = ft_strlen(path);
	full_path = malloc_perex(*path_len, "Malloc error on full_path");
	return (full_path);
}

char	*find_path(char *cmd, t_env *env_list)
{
	size_t	path_len;
	char	*path;
	char	*full_path;
	char	*direct_result;

	direct_result = check_direct_path(cmd);
	if (direct_result)
		return (direct_result);
	full_path = init_fullpath(env_list, &path_len);
	if (!full_path)
		return (NULL);
	path = find_envvar(env_list, "PATH")->val;
	return (process_dirs(path, cmd, full_path, path_len));
}
