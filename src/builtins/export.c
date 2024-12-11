#include "./builtins.h"

/**add_envvar adds either a newly defined environmental variable or updates
 * (changes) the value of an already existing one. First it tries to find if a
 * variable with the name already exists (by find_envvar), if not, then make a
 * new one (by create_envvar) and connct it to env_list.
 * 		Takes env_list from the main, and a key-value pair (KEY=value).
 * 		Returns nothing (but modifies env_list).
 */
void	add_envvar(t_env **env_list, const char *key, const char *val)
{
	t_env *existing;
	t_env *new_node;

	existing = find_envvar(*env_list, key);
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
		new_node->next = *env_list;
		*env_list = new_node;
	}
}

/**Create a single new node that can be added to the env_list.
 * 		Takes a key-value pair (KEY=value).
 * 		Returns the node.
 */
t_env	*create_envvar(const char *key, const char *val)
{
	t_env *new_node;

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
t_env	*find_envvar(t_env *env_list, const char *key)
{
	int	i;

	i = 0;
	while (key[i])
		i++;
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, i) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	//printf("%s=\"%s\"\n", env_list->key, env_list->val);
	return (NULL);
}

/**This function printfs env_list by iterating it. Some key may not have val, 
 * hence the if-else. 
 * 		Takes the env_list.
 * 		Returns nothing, it's a void function.
 */
void	print_envlist(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->val)
			printf("declare -x %s=\"%s\"\n", env_list->key, env_list->val);
		else
			printf("declare -x %s=\"\"\n", env_list->key);
		env_list = env_list->next;
	}
}

/**This is the implementation of export. It either prints env_list when no args
 * are given in the simple command, or add/update the env_list if there is one.
 * When that happens, the func loops over the args and finds the eq sign. The 
 * eq_sign is then replaced with a null terminator to split the string to key
 * (args[i]) and value (eq_sign+1) which then are passed to add_envvar. The 
 * eq_sign is then restored to =. If no eq sign is found, then add_envvar is
 * called without val.
 * 		Takes the whole args in simple command (incl args[0] --> the command, 
 * 			has to be skipped, hence the check for args[1]), and env_list.
 * 		Returns 0 because always success that will be transferred to the
 * 			calling executor.
*/
int	rh_export(char *args[], t_env **env_list)
{
	int		i;
	char	*eq_sign;
	char	*val;

	if (!args[1])
	{
		print_envlist(*env_list);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		eq_sign = ft_strchr(args[i], '=');
		if (eq_sign)
		{
			*eq_sign = '\0';
			val = eq_sign + 1;
			add_envvar(env_list, args[i], val);
			*eq_sign = '=';
		}
		else
			add_envvar(env_list, args[i], NULL);
		i++;
	}
	return (0);
}
