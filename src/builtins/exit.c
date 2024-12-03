#include "./builtins.h"

int	exit_cleanup(int n)
{	
	// free(input);
	// free_tkn(tokens);
	// free_ast(tree);
	// free_commtab(table);
	exit(n);
}