#include "./parser.h"

t_commtab *ast_to_commtab(t_ast *tree)
{
	t_commtab *table;

	table = create_commtab();
	traverse_ast(tree, table);
	return (table);
}

t_commtab *create_commtab() {
	t_commtab *table;
	
	table = malloc(sizeof(t_commtab));
	if (!table)
		return NULL;
	table->commands = NULL;
	table->count = 0;
	return (table);
}

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
	else if (node->type == NODE_REDIRECTION)
	{
		traverse_ast(node->left, table);
	}
	else if (node->type == NODE_SUBSHELL)
		traverse_ast(node->left, table);
	else if (node->type == NODE_INVALID)
		fprintf(stderr, "Invalid AST node detected.\n");
}

t_simcomm *create_simcomm(t_ast *node)
{
	t_simcomm *cmd = malloc(sizeof(t_simcomm));
	if (!cmd)
		return NULL;
	cmd->args = node->args;
	cmd->in_redir = NULL;
	cmd->out_redir = NULL;
	cmd->is_bg = 0;
	return (cmd);
}

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