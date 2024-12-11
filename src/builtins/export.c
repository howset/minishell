#include "./builtins.h"
#include <string.h>


//add /update environment variable, setenv adds to system environ (remove?)
void add_or_update_env(t_env **env_list, const char *key, const char *val)
{
	t_env *existing;
	t_env *new_var;

	existing = find_envvar(*env_list, key);
	if (existing)
	{
		free(existing->val);
		if (val)
			existing->val = strdup(val);
		else
			existing->val = NULL;
	}
	else
	{
		new_var = create_envvar(key, val);
		new_var->next = *env_list;
		*env_list = new_var;
	}
/* 	if (val)
	{
		if (setenv(key, val, 1) != 0)
			perror("setenv");
	} */
}

//createnew environment variable node
t_env *create_envvar(const char *key, const char *val)
{
	t_env *new_var;

	new_var = malloc_perex(sizeof(t_env), "Malloc error on create_env_var");
	new_var->key = ft_strdup(key);
	if (val)
		new_var->val = strdup(val);
	else
		new_var->val = NULL;
	new_var->next = NULL;
	return (new_var);
}

//find an environment variable (key)
t_env *find_envvar(t_env *env_list, const char *key)
{
	int	i;

	i = 0;
	while (key[i])
		i++;
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, i) == 0)
			return env_list;
		env_list = env_list->next;
	}
	return (NULL);
}

//print all environment variables
void print_envvar(t_env *env_list)
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

//the export command implementation
int rh_export(char *args[], t_env **env_list)
{
	int		i;
	char	*eq_sign;

	if (!args[1])
	{
		print_envvar(*env_list);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		eq_sign = ft_strchr(args[i], '=');
		if (eq_sign)
		{
			*eq_sign = '\0'; //temporarily split key and value
			add_or_update_env(env_list, args[i], eq_sign + 1);
			*eq_sign = '='; //restore original string
		}
		else
			add_or_update_env(env_list, args[i], NULL);
		i++;
	}
	return (0);
}
