#include "./builtins.h"

void echo(long long int arg_c, char *args[], int opt)
{
	int i;
	
	if (arg_c > 0)
	{
		i = 0;
		while (i < arg_c)
		{
			printf("%s ", args[i]);
			if (i < arg_c - 1)
				printf(" ");
			i++;
		}
	}
	if (opt == 0)
		printf("\n");
	return;
}