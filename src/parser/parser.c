/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:33:30 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/28 23:31:43 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

t_ast	*parse_command(t_token **current)
{
	t_ast	*node;
	char	*value;

	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	// Collect arguments until we hit an operator or EOF
	//	while (*current && ((*current)->type == TKN_WORD)
	while (*current && ((*current)->type == TKN_WORD
			|| (*current)->type == TKN_VAR || (*current)->type == TKN_QUO_SIN
			|| (*current)->type == TKN_QUO_DOU || (*current)->type == TKN_BG))
	{
		node->args_count++;
		node->args = realloc(node->args, sizeof(char *) * (node->args_count
					+ 1));
		value = ft_strdup((*current)->value);
		if ((*current)->type == TKN_VAR)
		{
			value = "should be replaced here";
		}
		node->args[node->args_count - 1] = value;
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
			if (*current != NULL)
				syntax_error_at((*current)->position, "Unmatched parenthesis");
			else
				syntax_error_at(-1, "Unmatched parenthesis");
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
			if (*current)
				syntax_error_at((*current)->position,
					"Expected a filename after redirection");
			else
				syntax_error_at(-1, "Expected a filename after redirection");
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
		if ((*current)->type == TKN_AND)
			type = NODE_AND;
		else if ((*current)->type == TKN_OR)
			type = NODE_OR;
		else
			type = NODE_SEQUENCE;
		op_node = create_ast_node(type);
		(*current) = (*current)->next; // Skip '&&', '||', or ';'
		op_node->left = node;
		op_node->right = parse_pipe(current);
		if (op_node->right == NULL)
		{
			if (*current)
				syntax_error_at((*current)->position,
					"Expected a command after logical operator");
			else
				syntax_error_at(-1,
					"Expected a command after logical operator");
			return (NULL);
		}
		node = op_node;
	}
	return (node);
}

t_ast	*parse(t_token *tokens, t_env **env_list)
{
	t_token	*current;

	current = tokens;
	return (parse_expression(&current));
}
