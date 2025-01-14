/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:42:21 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

// exec.c
int		exec_commtab(t_cmdtable *table, t_env **env_list, char *envp[]);
int		exec_builtin(char *args[], t_env **env_list, char *envp[]);
//int		exec_simprog(char *args[], t_env **env_list, char *envp[]);
int	exec_simprog(t_command *cmd, t_env **env_list, char *envp[]);
//int		exec_prog(t_command *cmd, t_env *env_list, char *envp[]);
int		exec_simple_command(t_command *cmd, t_env **env_list, char *envp[]);
int		exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[]);
int		is_builtin(char *cmd);

// exec_child
int		exec_chprocess(t_command *cmd, t_env **env_list, char *envp[]);
int		wait_chprocess(pid_t p_id);

// exec_pathfinding.c
char	*find_path(char *cmd, t_env *env_list);
char	*init_fullpath(t_env *env_list, size_t *path_len);
char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len);
char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len);

// exec_redirections.c
void	handle_input_redirection(t_redirection *redirection);
void	handle_output_redirection(t_redirection *redirection);
void	exec_redirections(t_redirection *redirections);

// Child process execution helper functions
int		handle_empty_command(t_command *cmd);
int		handle_builtin(t_command *cmd, t_env **env_list, char *envp[]);
void	handle_external_command(t_command *cmd, t_env **env_list, char *envp[]);

// Pipe command execution helper functions
void	handle_pipe_io(t_command *cmd);
void	close_pipe_fds(t_command *cmd);
int		fork_pipe_process(t_command *cmd, t_env **env_list, char *envp[]);

// Input redirection helper functions
void	handle_simple_input(t_redirection *redirection);
void	handle_heredoc_input(t_redirection *redirection);
void	process_heredoc_child(int write_fd, char *delimiter);
void	process_heredoc_parent(int read_fd, pid_t child_pid);

// Path finding helper functions
int		check_directory(char *cmd);
int		check_executable(char *cmd);
char	*handle_absolute_path(char *cmd);
char	*handle_path_search(char *cmd, t_env *env_list);

#endif
