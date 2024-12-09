#include "./builtins.h"

/**This function deals with quotes. First, check which quote (single/double).
 * Then if quote is double, then \t or \n will be interpreted as such.
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
			continue;
		}
		if (quote == '"' && arg[i] == '\\')
		{
			i++;
			if (!arg[i])
				break;
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

/**This implementation of echo now *writes* every string in the array args by
 * iterating it one by one. This is more useful as control to make sure that 
 * echo ONLY goes to stdout. If somehow it fails, it should return a different
 * exit_status (1) instead of the default (0).
 * If the opt is 1, then dont end with a newline, otherwise print it.
 * 		Takes the args array as argument, including the boolean int opt.
 * 		Returns the exit_status 0 as the default, if somehow writing to stdout
 * 			fails, returns exit_status 1.
 */
int	rh_echo(char *args[], int opt)
{
	int i;
	
	i = 0;
	while (args[i])
	{
		if (i > 0)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				perror("echo: write error");
				return (EXIT_FAILURE);
			}
		}
		if (print_quotedstr(args[i]) != EXIT_SUCCESS)
		{
			perror("echo: write error");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (opt == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
