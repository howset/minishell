#include "./builtins.h"

//swap two nodes
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

//sort alphabetically (by key) --> bubble sort
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

//print the sorted environment list
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
