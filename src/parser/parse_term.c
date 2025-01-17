/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:54:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/17 19:45:54 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

/**
 * parse_term - Parses a term from the token stream.
 * @current: Double pointer to the current token in the token stream.
 * @all_data: Pointer to the structure containing all necessary data.
 *
 * This function parses a term by first parsing a factor and then
 * handling any subsequent redirection or argument tokens. If a factor
 * cannot be parsed, it returns NULL. If a redirection or argument token
 * is encountered, it calls the appropriate handler function. If any
 * handler function fails, it returns NULL.
 *
 * Return: A pointer to the parsed AST node, or NULL on failure.
 */
t_ast	*parse_term(t_token **current, t_alldata *all_data)
{
	t_ast	*node;

	node = parse_factor(current, all_data);
	if (!node)
		return (NULL);
	while (*current && (is_redirection_token((*current)->type)
			|| is_argument_token((*current)->type)))
	{
		if (is_redirection_token((*current)->type))
		{
			if (!handle_redir(current, all_data, &node))
				return (NULL);
		}
		else
		{
			if (!handle_arg(current, all_data, node))
				return (NULL);
		}
	}
	return (node);
}

/**
 * handle_redir - Handles redirection tokens in the parsing process.
 * @current: Double pointer to the current token in the token list.
 * @all_data: Pointer to the structure containing all relevant data.
 * @node: Double pointer to the current AST node.
 *
 * This function processes redirection tokens, creates a new AST node for the
 * redirection, and links it to the current AST node. It also sanitizes the
 * filename associated with the redirection and duplicates it for the AST node.
 *
 * Return: 1 on success, 0 on failure.
 */
int	handle_redir(t_token **current, t_alldata *all_data, t_ast **node)
{
	t_ast	*redir_node;
	char	*filename;

	redir_node = create_ast_node(NODE_REDIRECTION);
	if (!redir_node)
		return (0);
	redir_node->redirection_type = (*current)->type;
	(*current) = (*current)->next;
	if (!check_redirtarget(current))
		return (0);
	filename = sanitize_text((*current)->value, all_data);
	redir_node->filename = ft_strdup(filename);
	(*current) = (*current)->next;
	redir_node->left = *node;
	*node = redir_node;
	free(filename);
	return (1);
}

/**
 * @brief Checks if the current token is a valid redirection target.
 *
 * This function verifies that the current token is not NULL and that it is
 * a valid argument token, which is required to be a filename after a 
 * redirection. If the token is invalid, a syntax error is reported.
 *
 * @param current A double pointer to the current token.
 * @return int Returns 1 if the current token is a valid redirection target,
 *         otherwise returns 0.
 */
int	check_redirtarget(t_token **current)
{
	if (!(*current))
	{
		syntax_error_at(-1, "Expected a filename after redirection");
		return (0);
	}
	if (!is_argument_token((*current)->type))
	{
		syntax_error_at((*current)->position,
			"Expected a filename after redirection");
		return (0);
	}
	return (1);
}

/**
 * handle_arg - Handles an argument token and adds it to the command node's
 * arguments.
 * @current: Double pointer to the current token being processed.
 * @all_data: Pointer to the structure containing all relevant data.
 * @node: Pointer to the current AST node.
 *
 * This function processes an argument token and adds it to the arguments list
 * of the command node in the AST. It first traverses the AST to find the
 * command node, skipping any redirection nodes. If the command node is not
 * found or is not of type NODE_COMMAND, it reports a syntax error. Otherwise,
 * it reallocates memory for the arguments list, duplicates the sanitized
 * argument value, and adds it to the list. The current token pointer is then
 * advanced to the next token.
 *
 * Return: 1 on success, 0 on syntax error.
 */
int	handle_arg(t_token **current, t_alldata *all_data, t_ast *node)
{
	t_ast	*command_node;

	command_node = node;
	while (command_node && command_node->type == NODE_REDIRECTION)
		command_node = command_node->left;
	if (!command_node || command_node->type != NODE_COMMAND)
	{
		syntax_error_at((*current)->position, "Unexpected argument token");
		return (0);
	}
	command_node->args_count++;
	command_node->args = ft_realloc(command_node->args,
			sizeof(char *) * command_node->args_count,
			sizeof(char *) * (command_node->args_count + 1));
	command_node->args[command_node->args_count - 1]
		= ft_strdup(sanitize_text((*current)->value, all_data));
	command_node->args[command_node->args_count] = NULL;
	(*current) = (*current)->next;
	return (1);
}
