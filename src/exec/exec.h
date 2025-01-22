/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:42:21 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:54:41 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

// ... existing code ...

// exec_redirections.c
void		handle_heredoc_child(int *pipefd, char *delimiter);
void		handle_heredoc_parent(int *pipefd, pid_t pid);
void		setup_heredoc(t_redirection *redirection);
void		handle_input_file(char *filename);

// exec_redirections2.c
void		handle_input_redirection(t_redirection *redirection);
void		handle_output_file(char *filename, int append);
void		handle_output_redirection(t_redirection *redirection);
void		exec_redirections(t_redirection *redirections);

// exec_child.c
int			is_builtin(char *cmd);
void		restore_fds(int stdin_backup, int stdout_backup);
int			exec_builtin(t_command *cmd, t_env **env_list, char *envp[]);
int			execute_builtin_command(t_command *cmd, t_env **env_list,
				char *envp[]);

// exec_child2.c
void		handle_empty_command(t_command *cmd);
void		execute_command(char *cmd_path, t_command *cmd, char *envp[]);
int			exec_chprocess(t_command *cmd, t_env **env_list, char *envp[]);
void		handle_sigquit(void);
int			wait_chprocess(pid_t p_id);

// exec_pathfinding.c
void		handle_direct_path(char *cmd);
char		*check_direct_path(char *cmd);
char		*init_fullpath(t_env *env_list, size_t *path_len);
char		*find_path(char *cmd, t_env *env_list);

// exec_pathfinding2.c
char		*try_path(char *full_path, char *start, char *cmd, size_t path_len);
void		handle_path_segment(char **end, char c);
char		*process_dirs(char *path, char *cmd, char *full_path,
				size_t path_len);
void		copy_path_components(char *full_path, char *dir, char *cmd,
				size_t path_len);
char		*build_fullpath(char *full_path, char *dir, char *cmd,
				size_t path_len);

// exec.c
int			exec_simple_command(t_command *cmd, t_env **env_list, char *envp[]);
int			exec_simprog(t_command *cmd, t_env **env_list, char *envp[]);
int			exec_commtab(t_cmdtable *table, t_env **env_list, char *envp[]);

// exec_pipe.c
void		setup_pipe_fds(int prev_pipe[2], int new_pipe[2], int is_last);
void		cleanup_pipes(int prev_pipe[2], int new_pipe[2], int has_next);
t_command	*find_last_pipe_cmd(t_command *cmd);
int			handle_last_builtin(t_command *cmd, int prev_pipe[2], t_env 
				**env_list, char *envp[]);
int			exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[]);

#endif
