#include "./builtins.h"

int rh_echo(char *args[])
{
	int i;
	int opt;
	int first_arg;

	opt = 0;
	i = 1;
	while (args[i] && check_n(args[i]))
	{
		opt = 1;
		i++;
	}
	first_arg = 1;
	while (args[i])
	{
		if (!first_arg)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				perror("echo: write error");
				return (EXIT_FAILURE);
			}
		}
		if (write(STDOUT_FILENO, args[i], ft_strlen(args[i])) == -1)
		{
			perror("echo: write error");
			return (EXIT_FAILURE);
		}
		first_arg = 0;
		i++;
	}
	if (!opt)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			perror("echo: write error");
			return (EXIT_FAILURE);
		}
	}
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
