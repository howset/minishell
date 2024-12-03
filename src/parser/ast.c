#include "./parser.h"

t_ast	*create_ast_node(t_nodetype type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL); // Handle malloc failure
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args = malloc(sizeof(char *));
	node->args[0] = NULL;
	node->redirection_type = TKN_INVALID;
	node->args_count = 0;
	node->filename = NULL;
	return (node);
}

void	print_ast(t_ast *node, int level)
{
	if (!node)
		return ;
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("Node type: %d\n", node->type);
	if (node->args)
	{
		for (int i = 0; node->args[i]; i++)
		{
			for (int j = 0; j < level; j++)
				printf("      ");
			printf("Arg %d: %s\n", i, node->args[i]);
		}
	}
	if(node->redirection_type != TKN_INVALID)
	{
		for (int i = 0; i < level; i++)
			printf("       ");
		printf("Redirection type: %d\n", node->redirection_type);
		for (int i = 0; i < level; i++)
			printf("       ");
		printf("Filename: %s\n", node->filename);
	}
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}
