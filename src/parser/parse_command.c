/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:54:30 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/17 14:10:09 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

t_ast	*parse_command(t_token **current, t_alldata *all_data)
{
	t_ast	*node;

	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	while (*current && ((*current)->type == TKN_WORD
			|| (*current)->type == TKN_VAR || (*current)->type == TKN_QUO_SIN
			|| (*current)->type == TKN_QUO_DOU || (*current)->type == TKN_BG))
	{
		if (process_tkn(current, node, all_data))
			continue ;
	}
	return (node);
}

int	process_tkn(t_token **current, t_ast *node, t_alldata *all_data)
{
	char	*sanitized;

	if ((*current)->type == TKN_VAR
		&& ft_strcmp((*current)->value, "$EMPTY") == 0)
	{
		(*current) = (*current)->next;
		return (1);
	}
	node->args_count++;
	node->args
		= ft_realloc(node->args, sizeof(char *) * (node->args_count + 1));
	sanitized = sanitize_text((*current)->value, all_data);
	node->args[node->args_count - 1] = ft_strdup(sanitized);
	free(sanitized);
	node->args[node->args_count] = NULL;
	(*current) = (*current)->next;
	return (0);
}
