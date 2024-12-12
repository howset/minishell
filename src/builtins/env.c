#include "./builtins.h"

/**Iterates the envp that is passed from the calling terminal (environ) and 
 * prints row by row. If the -ms option is given then prints the environmental
 * variables of **this** minishell.
 * 		Takes basically everything (args for the option, envp, and env_list).
 * 		Returns a zero because always success.
 * */
int	rh_env(char *args[], char *envp[], t_env **env_list)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		printf("-->The following are the variables in minishell.<--\n");
		while (*env_list)
		{
			if ((*env_list)->val)
				printf("%s=\"%s\"\n", (*env_list)->key, (*env_list)->val);
			else
				printf("%s=\"\"\n", (*env_list)->key);
			env_list = &(*env_list)->next;
		}
	}
	else if (ft_strncmp(args[1], "-g", 2) == 0)
	{
		printf("-->The following are the global variables environ.<--\n");
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	else
		printf("No option or option -g only");
	return (0);
}

//this can be confusing, but this aims to free the mallocs in create_envvar
/* void free_envlist(t_env *env_list)
{
	t_env *tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
} */

/**Ditched the ft_split because it fails to recognize val that contains other
 * equal signs. Now just find the first occurence of '=', and split to key and 
 * val. 
 * */
void	init_envlist(t_env **env_list, char *envp[])
{
	int		i;
	char	*key;
	char	*val;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (!equal_sign)
		{
			ft_fprintf(STDERR_FILENO, "Failed to find equal sign.\n");
			i++;
			continue ;
		}
		key = ft_substr(envp[i], 0, equal_sign - envp[i]);
		if (!key)
		{
			perror("Memory allocation failed for key");
			return ;
		}
		val = ft_strdup(equal_sign + 1);
		if (!val)
		{
			perror("Memory allocation failed for val");
			free(key);
			return ;
		}
		add_envvar(env_list, key, val);
		free(key);
		free(val);
		i++;
	}
}
