#include "./builtins.h"

//Swap keys and values of two t_env nodes
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

//Sort linked list alphabetically (by key) --> bubble sort
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

//Print the sorted environment list
void	print_envlist_sorted(t_env *env_list)
{
	t_env	*current;

	if (!env_list)
		return ;
	sort_envlist(&env_list);
	current = env_list;
	while (current)
	{
		if (current->val)
			printf("declare -x %s=\"%s\"\n", current->key, current->val);
		else
			printf("declare -x %s=\"\"\n", current->key);
		current = current->next;
	}
}
