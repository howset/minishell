#include "./builtins.h"

int	rh_env(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}