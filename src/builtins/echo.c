#include "./builtins.h"

int	rh_echo(char *args[])
{
	int	i;
	int	opt;

	opt = 0;
	i = 1;
	while (args[i] && check_n(args[i]))
	{
		opt = 1;
		i++;
	}
	while (args[i])
	{
		if (i > 1)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				perror("Echo: write error");
				return (EXIT_FAILURE);
			}
		}
		if (write(STDOUT_FILENO, args[i], ft_strlen(args[i])) == -1)
		{
			perror("Echo: write error");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (opt == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

int	check_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
