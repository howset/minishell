#include "./parser.h"

t_ast	*parse_command(t_token **current)
{
	t_ast	*node;

	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	// Collect arguments until we hit an operator or EOF
	while (*current && (*current)->type == TKN_WORD)
	{
		node->args_count++;
		node->args = realloc(node->args, sizeof(char *) * (node->args_count
					+ 1));
		node->args[node->args_count - 1] = ft_strdup((*current)->value);
		node->args[node->args_count] = NULL;
		(*current) = (*current)->next;
	}
	return (node);
}
t_ast	*parse_factor(t_token **current)
{
	t_ast	*node;

	if ((*current)->type == TKN_PAREN_OP)
	{
		(*current) = (*current)->next; // Skip '('
		node = parse_expression(current);
		if ((*current)->type != TKN_PAREN_CL)
		{
			syntax_error_at((*current) ? (*current)->position : -1,
				"Unmatched parenthesis");
			return (NULL);
		}
		(*current) = (*current)->next; // Skip ')'
	}
	else if ((*current)->type == TKN_WORD)
	{
		node = parse_command(current);
	}
	else
	{
		// Handle syntax error
		return (NULL);
	}
	return (node);
}
t_ast	*parse_term(t_token **current)
{
	t_ast	*node;
	t_ast	*redir_node;

	node = parse_factor(current);
	while (*current && ((*current)->type == TKN_RDIR_IN
			|| (*current)->type == TKN_RDIR_OUT
			|| (*current)->type == TKN_APPEND
			|| (*current)->type == TKN_HEREDOC))
	{
		redir_node = create_ast_node(NODE_REDIRECTION);
		redir_node->redirection_type = (*current)->type;
		(*current) = (*current)->next;
		if ((*current)->type != TKN_WORD)
		{
			syntax_error_at((*current) ? (*current)->position : -1,
				"Expected a filename after redirection");
			return (NULL);
		}
		redir_node->filename = ft_strdup((*current)->value);
		(*current) = (*current)->next;
		redir_node->left = node;
		node = redir_node;
	}
	return (node);
}
t_ast	*parse_pipe(t_token **current)
{
	t_ast	*node;
	t_ast	*pipe_node;

	node = parse_term(current);
	while (*current && (*current)->type == TKN_PIPE)
	{
		pipe_node = create_ast_node(NODE_PIPE);
		(*current) = (*current)->next; // Skip '|'
		pipe_node->left = node;
		pipe_node->right = parse_term(current);
		node = pipe_node;
	}
	return (node);
}
t_ast	*parse_expression(t_token **current)
{
	t_ast		*node;
	t_nodetype	type;
	t_ast		*op_node;

	node = parse_pipe(current);
	while (*current && ((*current)->type == TKN_AND
			|| (*current)->type == TKN_OR || (*current)->type == TKN_SEMCOL))
	{
		if (node == NULL)
		{
			syntax_error_at((*current)->position,
				"Unexpected logical operator without a preceding command");
			return (NULL);
		}
		type = (*current)->type == TKN_AND ? NODE_AND : (*current)->type == TKN_OR ? NODE_OR : NODE_SEQUENCE;
		op_node = create_ast_node(type);
		(*current) = (*current)->next; // Skip '&&', '||', or ';'
		op_node->left = node;
		op_node->right = parse_pipe(current);
		if (op_node->right == NULL)
		{
			syntax_error_at((*current) ? (*current)->position : -1,
				"Expected a command after logical operator");
			return (NULL);
		}
		node = op_node;
	}
	return (node);
}
t_ast	*parse(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	return (parse_expression(&current));
}
