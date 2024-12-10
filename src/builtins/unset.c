#include "./builtins.h"

void unset_command(char *args[], t_env **env_list)
{
	if (!args[1])
	{
		ft_fprintf(STDERR_FILENO, "unset: not enough arguments\n");
		return;
	}

	for (int i = 1; args[i]; i++)
	{
		t_env *prev = NULL;
		t_env *current = *env_list;

		while (current) {
			if (strcmp(current->key, args[i]) == 0) {
				// Found the variable to remove
				if (prev) {
					prev->next = current->next;
				} else {
					*env_list = current->next;
				}

				// Remove from environment (system)
				unsetenv(current->key);

				// Free memory
				free(current->key);
				free(current->value);
				free(current);
				break;
			}
			prev = current;
			current = current->next;
		}
	}
}