#include "./parser.h"

/**This function aims to convert a syntax tree to a command table.
 * 		Takes the resulting t_ast tree from the parser.
 * 		Returns a command table that contains (row-by-row) simple commands.
 * 			These can then be executed sequentially.
 */
t_commtab *ast_to_commtab(t_ast *tree)
{
	t_commtab *table;

	table = create_commtab();
	traverse_ast(tree, table);
	return (table);
}

/**This function initializes the t_commtab struct.
 * 		Takes no args.
 * 		Returns an empty initialized struct.
 */
t_commtab *create_commtab() {
	t_commtab *table;
	
	table = malloc_perex(sizeof(t_commtab), "Malloc error on create_commtab");
	table->commands = NULL;
	table->count = 0;
	return (table);
}

/**This function traverses the syntax tree and populates the command table.
 * It checks the type of the (root) node, and whenever a pipe or operator node
 * is found, the command table will be filled accordingly, i.e. left-side node
 * from the root will be recursively traversed and discovered as 1st simple 
 * command, and right-side node as the following command. Likewise for a redir
 * node but recursive traversal only to the left-side.
 * When a command node is found, the row of the command table (simple
 * command) will be filled.
 * 		Takes a node (the root) of the syntax tree as an argument as well as 
 * 			an (empty) initialized command table.
 * 		Returns a constructed command table.
 */
void traverse_ast(t_ast *node, t_commtab *table)
{
	t_simcomm *cmd;
	t_simcomm *last_cmd;

	if (!node)
		return;
	if (node->type == NODE_COMMAND) 
	{
		table->commands = realloc(table->commands, sizeof(t_simcomm) * (table->count + 1));
		if (!table->commands)
			return;
		cmd = create_simcomm(node);
		if (node->redirection_type == TKN_RDIR_IN)
			cmd->in_redir = ft_strdup(node->filename);
		else if (node->redirection_type == TKN_RDIR_OUT || node->redirection_type == TKN_APPEND)
			cmd->out_redir = ft_strdup(node->filename);
		table->commands[table->count] = *cmd;
		table->count++;
	}
	else if (node->type == NODE_REDIRECTION)
	{
		traverse_ast(node->left, table);
		if (table->count > 0)
		{
			last_cmd = &table->commands[table->count - 1];

			if (node->redirection_type == TKN_RDIR_IN)
				last_cmd->in_redir = ft_strdup(node->filename);
			else if (node->redirection_type == TKN_RDIR_OUT || node->redirection_type == TKN_APPEND)
				last_cmd->out_redir = ft_strdup(node->filename);
		}
	}
	else if (node->type == NODE_PIPE || node->type == NODE_AND || node->type == NODE_OR || node->type == NODE_SEQUENCE) 
	{ // '&&' '||' ';' actually *executes* differently
		traverse_ast(node->left, table);
		traverse_ast(node->right, table);
	}
	else if (node->type == NODE_SUBSHELL)
		traverse_ast(node->left, table);
	else if (node->type == NODE_INVALID)
		fprintf(stderr, "Invalid AST node detected.\n");
}

/**This function initializes the t_simmcom struct.
 * 		Takes a node from the syntax tree as the argument.
 * 		Returns an initialized struct where everything is empty except
 * 			the args field.
 */
t_simcomm *create_simcomm(t_ast *node)
{
	t_simcomm *cmd;
	
	cmd = malloc_perex(sizeof(t_simcomm), "Malloc error on create_simcomm");
	cmd->args = node->args;
	cmd->in_redir = NULL;
	cmd->out_redir = NULL;
	cmd->is_bg = 0;
	return (cmd);
}

/**This function just prints the content of the created command table. It runs
 * through the list/table row by row.
 * 		Takes the command table as argument.
 * 		Returns nothing.
 */
void print_commtab(t_commtab *table)
{
	int	i;
	int j;

	i = 0;
	while (i < table->count)
	{
		printf("\n");
		printf("Command %d:\n", i + 1);
		j = 0;
		while (table->commands[i].args[j])
		{
			printf("  Arg[%d]: %s\n", j, table->commands[i].args[j]);
			j++;
		}
		if (table->commands[i].in_redir)
			printf("  Input Redirection: %s\n", table->commands[i].in_redir);
		if (table->commands[i].out_redir)
			printf("  Output Redirection: %s\n", table->commands[i].out_redir);
		if (table->commands[i].is_bg)
			printf("  Background: Yes\n");
		else
			printf("  Background: No\n");
		i++;
	}
}