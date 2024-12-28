#include "./builtins.h"

/**Iterates the envp that is passed from the calling terminal (environ) and
 * prints row by row. When no option is given, then prints the variables in
 * **this** minishell, when `-g` is given, then prints the global environ
 * variables.
 * 		Takes basically everything (args for the option, envp, and env_list).
 * 		Returns a zero because always success.
 */
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
				printf("%s=%s\n", (*env_list)->key, (*env_list)->val);
			else
				printf("%s=\n", (*env_list)->key);
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
	return (EXIT_SUCCESS);
}
