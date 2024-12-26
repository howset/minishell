#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

// exec.c
int		exec_commtab(t_cmdtable *table, t_env **env_list, char *envp[]);
int		exec_builtin(char *args[], t_env **env_list, char *envp[]);
int		exec_prog(t_command *cmd, t_env *env_list, char *envp[]);
int		exec_simple_command(t_command *cmd, t_env *env_list, char *envp[]);
int		exec_pipe_command(t_command *cmd, t_env *env_list, char *envp[]);
int		is_builtin(char *cmd);

// exec_child
int		exec_chprocess(char **args, t_env *env_list, char *envp[]);
int		wait_chprocess(pid_t p_id);

// exec_pathfinding.c
char	*find_path(char *cmd, t_env *env_list);
char	*init_fullpath(t_env *env_list, size_t *path_len);
char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len);
char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len);

#endif
