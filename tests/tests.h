#ifndef TESTS_H
# define TESTS_H

# include "../src/builtins/builtins.h"
# include "../src/lexer/lexer.h"
# include "../src/minishell.h"
# include "../src/parser/parser.h"
# include <check.h>
# include <stdlib.h>
# include <string.h>

// Function prototypes
t_env	*create_env_var(char *key, char *val);
void	free_env_list(t_env *env_list);

#endif
