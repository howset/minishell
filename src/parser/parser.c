/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:33:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/01 19:59:22 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

static int	is_argument_token(t_tkntype type)
{
	return (type == TKN_WORD || type == TKN_VAR || type == TKN_QUO_SIN
		|| type == TKN_QUO_DOU || type == TKN_BG);
}

static int	is_redirection_token(t_tkntype type)
{
	return (type == TKN_RDIR_IN || type == TKN_RDIR_OUT || type == TKN_APPEND
		|| type == TKN_HEREDOC);
}

t_ast	*parse_command(t_token **current, t_alldata *all_data)
{
	t_ast	*node;

	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	// Collect arguments until we hit an operator or EOF
	//	while (*current && ((*current)->type == TKN_WORD)
	while (*current && ((*current)->type == TKN_WORD
			|| (*current)->type == TKN_VAR || (*current)->type == TKN_QUO_SIN
			|| (*current)->type == TKN_QUO_DOU || (*current)->type == TKN_BG))
	{
		if ((*current)->type == TKN_VAR && ft_strcmp((*current)->value,
				"$EMPTY") == 0)
		{
			(*current) = (*current)->next;
			continue ;
		}
		node->args_count++;
		node->args = realloc(node->args, sizeof(char *) * (node->args_count
					+ 1));
		node->args[node->args_count
			- 1] = ft_strdup(sanitize_text((*current)->value, all_data));
		node->args[node->args_count] = NULL;
		(*current) = (*current)->next;
	}
	return (node);
}

t_ast	*parse_factor(t_token **current, t_alldata *all_data)
{
	t_ast	*node;

	if ((*current)->type == TKN_PAREN_OP)
	{
		(*current) = (*current)->next; // Skip '('
		node = parse_expression(current, all_data);
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
	else if ((*current)->type == TKN_WORD || (*current)->type == TKN_VAR)
	{
		node = parse_command(current, all_data);
	}
	else
	{
		// Handle syntax error
		return (NULL);
	}
	return (node);
}

t_ast	*parse_term(t_token **current, t_alldata *all_data)
{
	t_ast	*node;
	t_ast	*redir_node;
	t_ast	*command_node;

	// First parse either a simple command, variable, etc., or '(' expression
	node = parse_factor(current, all_data);
	if (!node)
		return (NULL);
	/*
		* Keep looping if the next token is either:
		*  -- a redirection operator (<, >, >>, <<),
		*  -- or a token that can be appended as an argument (TKN_WORD, TKN_QUO,
			TKN_VAR...).
		* This allows us to handle sequences like:
		*   echo hi < file more_args >> another_file "another arg"
		*/
	while (*current && (is_redirection_token((*current)->type)
			|| is_argument_token((*current)->type)))
	{
		// If it's a redirection operator, parse it
		if (is_redirection_token((*current)->type))
		{
			redir_node = create_ast_node(NODE_REDIRECTION);
			if (!redir_node)
				return (NULL);
			redir_node->redirection_type = (*current)->type;
			(*current) = (*current)->next; // move past '<' or '>' etc.
			// Next token must be a valid "filename" token
			if (!(*current) || !is_argument_token((*current)->type))
			{
				if (*current)
					syntax_error_at((*current)->position,
						"Expected a filename after redirection");
				else
					syntax_error_at(-1,
						"Expected a filename after redirection");
				return (NULL);
			}
			redir_node->filename = ft_strdup(sanitize_text((*current)->value,
						all_data));
			(*current) = (*current)->next; // consume the filename token
			// attach previous node (command or pipeline or subshell) to the redirection's left
			redir_node->left = node;
			node = redir_node;
		}
		// Otherwise, if it's an argument token, append it to the command node
		else
		{
			/*
				* We need to find the underlying command node to attach extra arguments.
				* E.g. if 'node' is a chain of redirections,
					go down .left until we find
				* the actual NODE_COMMAND (echo, cat, grep, etc.).
				*/
			command_node = node;
			while (command_node && command_node->type == NODE_REDIRECTION)
				command_node = command_node->left;
			// If there's no command node at all, we can optionally create one
			// or throw an error. For a typical Bash-like shell, you might
			// create a new command node, but let's keep it simple:
			if (!command_node || command_node->type != NODE_COMMAND)
			{
				syntax_error_at((*current)->position,
					"Unexpected argument token");
				return (NULL);
			}
			// Append the new argument
			command_node->args_count++;
			command_node->args = realloc(command_node->args, sizeof(char *)
					* (command_node->args_count + 1));
			command_node->args[command_node->args_count
				- 1] = ft_strdup(sanitize_text((*current)->value, all_data));
			command_node->args[command_node->args_count] = NULL;
			(*current) = (*current)->next; // consume the argument token
		}
	}
	return (node);
}

t_ast	*parse_pipe(t_token **current, t_alldata *all_data)
{
	t_ast	*node;
	t_ast	*pipe_node;

	node = parse_term(current, all_data);
	while (*current && (*current)->type == TKN_PIPE)
	{
		pipe_node = create_ast_node(NODE_PIPE);
		(*current) = (*current)->next; // Skip '|'
		pipe_node->left = node;
		pipe_node->right = parse_term(current, all_data);
		node = pipe_node;
	}
	return (node);
}

t_ast	*parse_expression(t_token **current, t_alldata *all_data)
{
	t_ast		*node;
	t_nodetype	type;
	t_ast		*op_node;

	node = parse_pipe(current, all_data);
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
		op_node->right = parse_pipe(current, all_data);
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

t_ast	*parse(t_token *tokens, t_alldata *all_data)
{
	t_token	*current;

	current = tokens;
	return (parse_expression(&current, all_data));
}
