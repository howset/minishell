#include "envs.h"

/**add_envvar adds either a newly defined environmental variable or updates
 * (changes) the value of an already existing one. First it tries to find if a
 * variable with the name already exists (by find_envvar), if not, then make a
 * new one (by create_envvar) and connct it to env_list.
 * 		Takes env_list from the main, and a key-value pair (KEY=value).
 * 		Returns nothing (but modifies env_list).
 */
void	add_envvar(char *key, char *val)
{
	t_env	*existing;
	t_env	*new_node;
	t_env	*current;


	current = get_envlist();
	if (!current)
	{
		new_node = create_envvar(key, val);
		g_env = new_node;
		return ;
	}
	existing = find_envvar(key);
	if (existing)
	{
		if (existing->val)
			free(existing->val);
		if (val)
			existing->val = ft_strdup(val);
		else
			existing->val = NULL;
	}
	else
	{
		new_node = create_envvar(key, val);
		while (current->next)
			current = current->next;

		current->next = new_node;
	}
}

/**Create a single new node that can be added to the env_list.
 * 		Takes a key-value pair (KEY=value).
 * 		Returns the node.
 */
t_env	*create_envvar(char *key, char *val)
{
	t_env	*new_node;

	new_node = malloc_perex(sizeof(t_env), "Malloc error on create_env_var");
	new_node->key = ft_strdup(key);
	if (val)
		new_node->val = ft_strdup(val);
	else
		new_node->val = NULL;
	new_node->next = NULL;
	return (new_node);
}

/**Find a variable name (key) in the env_list. Iterates over the nodes in the
 * list, if found, return the node, if not, return NULL.
 * 		Takes env_list to search for key.
 * 		Returns the node in which key is found, otherwise NULL.
 */
t_env	*find_envvar(char *key)
{
	t_env	*current;
	int		i;

	current = get_envlist();
	i = 0;
	while (key[i])
		i++;
	while (current)
	{
		if (ft_strncmp(current->key, key, i) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	remove_envvar(char *key)
{
	t_env	*prev;
	t_env	*current;
	int		len;

	prev = NULL;
	current = get_envlist();
	len = ft_strlen(key);
	while (current)
	{
		if (ft_strncmp(current->key, key, len) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				current = current->next;
			free(current->key);
			free(current->val);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}
