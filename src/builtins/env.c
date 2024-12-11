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

//the one from ft_split
static void ft_freearr(char **arr, size_t count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
}

void init_envlist(t_env **env_list, char *envp[])
{
	int i;
	char *key;
	char *val;
	char **keyval_arr;

	i = 0;
	while (envp[i])
	{
		keyval_arr = ft_split(envp[i], '=');
		if (!keyval_arr || !keyval_arr[0])
		{
			ft_freearr(keyval_arr, 2);
			ft_fprintf(STDERR_FILENO, "Failed to parse environment variable");
			return;
		}
		key = ft_strdup(keyval_arr[0]);
		if (keyval_arr[1])
			val = ft_strdup(keyval_arr[1]);
		else
			val = NULL;
		ft_freearr(keyval_arr, 2);
		add_or_update_env(env_list, key, val);
		free(key);
		free(val);
		i++;
	}
}
