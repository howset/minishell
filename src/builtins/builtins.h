#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

// echo.c
int		rh_echo(char *args[]);
int		check_n(char *arg);
int		writing(char *str);

// env.c
int		rh_env(char *args[], char *envp[], t_env **env_list);

// exit.c
int		rh_exit(char *args[]);

// export.c
int		rh_export(char *args[], t_env **env_list);


// unset.c
int		rh_unset(char *args[], t_env **env_list);

// pwd.c
int		rh_pwd(void);
int		rh_cd(char *path);

#endif
