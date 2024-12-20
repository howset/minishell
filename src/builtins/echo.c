#include "./builtins.h"

/**This function deals with quotes. First, check which quote (single/double).
 * Then if quote is double, then \t or \n will be interpreted as such. -->
 * this is wrong!! must be fixed!!!!
 * 		Takes a word.
 * 		Returns success.
*/
static int	print_quotedstr(char *arg)
{
	int		i;
	char	quote;

	i = 0;
	if (arg[i] == '"' || arg[i] == '\'')
	{
		quote = arg[i];
		i++;
	}
	while (arg[i])
	{
		if (arg[i] == quote)
		{
			i++;
			continue ;
		}
		if (quote == '"' && arg[i] == '\\')
		{
			i++;
			if (!arg[i])
				break ;
			if (arg[i] == 'n')
				write(STDOUT_FILENO, "\n", 1);
			else if (arg[i] == 't')
				write(STDOUT_FILENO, "\t", 1);
			else if (arg[i] == '\\')
				write(STDOUT_FILENO, "\\", 1);
			else if (arg[i] == '"')
				write(STDOUT_FILENO, "\"", 1);
			else if (arg[i] == '\'')
				write(STDOUT_FILENO, "'", 1);
		}
		else
			write(STDOUT_FILENO, &arg[i], 1);
		i++;
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
		if (i > 2)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				perror("Echo: write error");
				return (EXIT_FAILURE);
			}
		}
		if (print_quotedstr(args[i]) != EXIT_SUCCESS)
		{
			perror("Echo: write error");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (opt == 0)
		write(STDOUT_FILENO, "\n", 1);
	else
		write(STDOUT_FILENO, "\0", 0);
	return (EXIT_SUCCESS);
}

