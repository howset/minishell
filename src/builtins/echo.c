#include "./builtins.h"

/**This implementation of echo just printfs every string in the array args by
 * iterating it one by one. If the opt is 1, then dont end with a newline,
 * otherwise print it.
 * 		Takes the args array as argument, including the boolean int opt.
 * 		Returns nothing
 */
void echo(char *args[], int opt)
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
	return;
}