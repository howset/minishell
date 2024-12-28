#include "envs.h"

// this aims to free the mallocs from create_envvar
void	free_envlist(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->val)
			free(tmp->val);
		free(tmp);
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
void	sort_envlist(t_env **env_list)
{
	t_env	*current;
	t_env	*next;
	int		swapped;
	int		key_len;

	if (!env_list || !*env_list)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *env_list;
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
void	print_sortedenvlist(t_env *env_list)
{
	if (!env_list)
		return ;
	sort_envlist(&env_list);
	while (env_list)
	{
		if (env_list->val)
			printf("declare -x %s=\"%s\"\n", env_list->key, env_list->val);
		else
			printf("declare -x %s=\"\"\n", env_list->key);
		env_list = env_list->next;
	}
}
