#include "./parser.h"

void	free_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->args)
	{
		for (int i = 0; i < ast->args_count; i++)
		{
			free(ast->args[i]);
		}
		free(ast->args);
	}
	if (ast->filename)
		free(ast->filename);
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}

void	consume_token(t_token **current)
{
	if (*current != NULL)
	{
		*current = (*current)->next;
	}
}

t_tkntype	get_token_type(t_token **current)
{
	if (*current != NULL)
	{
		return ((*current)->type);
	}
	return (TKN_EOF);
}

void	parse_error(const char *message, t_token *token)
{
	if (token && token->value)
	{
		fprintf(stderr, "Parse error near '%s': %s\n", token->value, message);
	}
	else
	{
		fprintf(stderr, "Parse error: %s\n", message);
	}
	// TODO FOR LATER: Handle error as needed (e.g., set an error flag,
	// clean up, etc.)
}

void	syntax_error(const char *message)
{
	fprintf(stderr, "Syntax error: %s\n", message);
}

void	syntax_error_at(int position, const char *message)
{
	fprintf(stderr, "Syntax error at position %d: %s\n", position, message);
}
