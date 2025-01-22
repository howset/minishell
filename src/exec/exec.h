/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:42:21 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 22:27:37 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

// exec.c
int			exec_commtab(t_cmdtable *table, t_env **env_list, char *envp[]);
int			exec_simple_command(t_command *cmd, t_env **env_list, char *envp[]);
int			exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[]);
t_command	*find_last_pipe_command(t_command *cmd);
void		setup_pipes(int *prev_pipe, int *new_pipe, int has_next);

//exec_spillover.c
int			exec_last_builtin(t_command *cmd, t_env **env_list, char *envp[],
				int *prev_pipe);
void		handle_child_process(t_command *cmd, int *pipes, t_env **env_list,
				char *envp[]);
int			fork_and_handle(t_command *cmd, int *pipes, t_env **env_list,
				char *envp[]);
void		update_pipes(int *prev_pipe, int *new_pipe, int has_next);

//exec_spillover2.c
int			wait_for_children(int *status);

// exec_child
int			is_builtin(char *cmd);
int			handle_builtin_command(t_command *cmd, t_env **env_list,
				char *envp[]);
int			exec_builtin(t_command *cmd, t_env **env_list, char *envp[]);
int			exec_chprocess(t_command *cmd, t_env **env_list, char *envp[]);
int			wait_chprocess(pid_t p_id);

// exec_pathfinding.c
char		*find_path(char *cmd, t_env *env_list);
char		*handle_direct_path(char *cmd);
char		*init_fullpath(t_env *env_list, size_t *path_len);
char		*process_dirs(char *path, char *cmd, char *full_path,
				size_t path_len);
char		*build_fullpath(char *full_path, char *dir, char *cmd,
				size_t path_len);

// exec_redirections.c
void		handle_output_redirection(t_redirection *redirection);
void		exec_redirections(t_redirection *redirections);

// exec_redirections_input.c
void		handle_simple_input(t_redirection *redirection);
void		handle_heredoc_child(int *pipefd, char *delimiter);
void		handle_heredoc_parent(int *pipefd, pid_t pid);
void		handle_heredocc(t_redirection *redirection);
void		handle_input_redirection(t_redirection *redirection);

#endif
