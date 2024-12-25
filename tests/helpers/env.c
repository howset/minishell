#include "../tests.h"

// Helper function to create a new environment variable
t_env	*create_env_var(char *key, char *val)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	new_var->key = strdup(key);
	new_var->val = strdup(val);
	new_var->next = NULL;
	return (new_var);
}

// Helper function to free the environment list
void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
}
