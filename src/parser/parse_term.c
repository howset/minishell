/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:54:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/16 17:54:01 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

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
			sizeof(char *) * (command_node->args_count + 1));
	command_node->args[command_node->args_count - 1]
		= ft_strdup(sanitize_text((*current)->value, all_data));
	command_node->args[command_node->args_count] = NULL;
	(*current) = (*current)->next;
	return (1);
}
