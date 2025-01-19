/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:42:21 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 01:54:24 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

// exec.c
int		exec_commtab(t_cmdtable *table, t_env **env_list, char *envp[]);
int		exec_simprog(t_command *cmd, t_env **env_list, char *envp[]);
int		exec_simple_command(t_command *cmd, t_env **env_list, char *envp[]);
int		exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[]);
int		waiting_pipeline(int status);

// exec_child
int		is_builtin(char *cmd);
int		exec_builtin(char *args[], t_env **env_list, char *envp[]);
int		exec_chprocess(t_command *cmd, t_env **env_list, char *envp[]);
int		wait_chprocess(pid_t p_id);

// exec_pipes.c
int		process_pipeline(t_command *curr, t_pipeline_data *data);
int		handle_lastbuiltin(t_command *curr, t_pipeline_data *data);
int		setup_pipe(t_command *cmd, int new_pipe[2]);
int		fork_exec(t_command *curr, t_pipeline_data *data, int new_pipe[2]);
void	handle_chprocess(t_command *curr, t_pipeline_data *data,
			int new_pipe[2]);

// exec_pathfinding.c
char	*find_path(char *cmd, t_env *env_list);
char	*resolve_path(char *cmd, t_env *env_list, size_t *path_len);
char	*init_fullpath(t_env *env_list, size_t *path_len);

// exec_pathfinding_build.c
char	*try_access(char *full_path, char *start, char *cmd, size_t path_len);
char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len);
char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len);

// exec_redirections.c
void	handle_input_redirection(t_redirection *redirection);
void	handle_output_redirection(t_redirection *redirection);
void	exec_redirections(t_redirection *redirections);

// exec_redirs_in.c
void	handle_filein(t_redirection *redirection);
void	handle_heredocin(t_redirection *redirection);
void	exec_childheredoc(t_redirection *redirection, int pipefd[2]);
void	exec_parentheredoc(int pipefd[2], pid_t pid);

#endif
