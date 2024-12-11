#include "./builtins.h"

/**This imitation of unset basically just tries to match the given key to the 
 * key-value pair in the env_list. If the key is found, then remove the 
 * key-value pair. If it is not found, do nothing.
 * 		Takes the args from the simple command and env_list.
 * 		Returns the exit status (always 0, except when no args given)
*/
int	rh_unset(char *args[], t_env **env_list)
{
	int	i;
	int	len;
	t_env *prev;
	t_env *current;

	if (!args[1])
	{
		ft_fprintf(STDERR_FILENO, "unset: not enough arguments\n");
		return (1);
	}
	i = 1;
	while (args[i])
	{
		prev = NULL;
		current = *env_list;
		len = ft_strlen(args[i]);
		while (current)
		{
			if (ft_strncmp(current->key, args[i], len) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					*env_list = current->next;
				free(current->key);
				free(current->val);
				free(current);
				break;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}