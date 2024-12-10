#include "./builtins.h"

int	rh_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

//this can be confusing, but this frees the mallocs in create_envvar
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

void init_envlist(t_env **env_list, char *envp[])
{
	int i;
	char *eq;
	char *key;
	char *val;
	char	**keyval_arr;

	i = 0;
	while (envp[i])
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			keyval_arr = ft_split(envp[i], '=');
			key = ft_strdup(keyval_arr[0]);
			if (val)
				val = ft_strdup(keyval_arr[1]);
			free(keyval_arr);
			add_or_update_env(env_list, key, val);
			free(key);
			free(val);
		}
		i++;
	}
}