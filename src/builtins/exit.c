#include "./builtins.h"

int	rh_exit(char *args)
{
	int ex_stat;

	ex_stat = ft_atoi(args);
	if (ex_stat == 0)
	{
		perror("exit: numeric argument required");
		exit (2);
	}
	exit(ex_stat);
}