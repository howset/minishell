#include "./builtins.h"

/**This implementation of echo just printfs every string in the array args by
 * iterating it one by one. If the opt is 1, then dont end with a newline,
 * otherwise print it.
 * 		Takes the args array as argument, including the boolean int opt.
 * 		Returns nothing
 */
/* int echo(char *args[], int opt)
{
	int i;
	
	i = 0;
	while (args[i])
	{
		if (i > 0)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (opt == 0)
		printf("\n");
	return (0);
} */

/**This implementation of echo now *writes* every string in the array args by
 * iterating it one by one. This is more useful as control to make sure that 
 * echo ONLY goes to stdout. If somehow it fails, it should return a different
 * exit_status (1) instead of the default (0).
 * If the opt is 1, then dont end with a newline, otherwise print it.
 * 		Takes the args array as argument, including the boolean int opt.
 * 		Returns the exit_status 0 as the default, if somehow writing to stdout
 * 			fails, returns exit_status 1.
 */
int rh_echo(char *args[], int opt)
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
		if (write(STDOUT_FILENO, args[i], ft_strlen(args[i])) == -1)
		{
			perror("echo: write error");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (opt == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}