#include "envs.h"

t_env	*g_env = NULL;

t_env	*get_envlist(void)
{
	return (g_env);
}
// this aims to free the mallocs from create_envvar
void	free_envlist(void)
{
	t_env	*current;

	current = get_envlist();
	while (current)
	{
		free(current->key);
		free(current->val);
		free(current);
		current = current->next;
	}
}

/**Ditched the ft_split because it fails to recognize val that contains other
 * equal signs. Now just find the first occurence of '=', and split to key and
 * val.
 * This function initializes the env_list by going over envp row-by-row, finds
 * the `=`, then separates the string before and after the eq sign as key and
 * val. Both key and val are then put into env_list via `add_envvar`.
 * 		Takes the envp from main and declared env_list in main.
 * 		Returns nothing because void func, but initializes the env_list.
 */
void	init_envlist(char *envp[])
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
		add_envvar(key, val);
		free(key);
		free(val);
		i++;
	}
}

// swap two nodes
void	swap_envvar(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_val;

	temp_key = a->key;
	temp_val = a->val;
	a->key = b->key;
	a->val = b->val;
	b->key = temp_key;
	b->val = temp_val;
}

// sort alphabetically (by key) --> bubble sort
void	sort_envlist(void)
{
	t_env	*current;
	t_env	*next;
	int		swapped;
	int		key_len;

	if (!g_env)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = get_envlist();
		while (current && current->next)
		{
			next = current->next;
			key_len = ft_strlen(current->key) + 1;
			if (ft_strncmp(current->key, next->key, key_len) > 0)
			{
				swap_envvar(current, next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}

// print the sorted environment list
void	print_sortedenvlist(void)
{
	t_env	*env;

	if (!g_env)
		return ;
	sort_envlist();
	env = g_env;
	while (env)
	{
		if (env->val)
			printf("declare -x %s=\"%s\"\n", env->key, env->val);
		else
			printf("declare -x %s=\"\"\n", env->key);
		env = env->next;
	}
}
