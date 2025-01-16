/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:57:14 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/16 18:21:50 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

t_ast	*parse_pipe(t_token **current, t_alldata *all_data)
{
	t_ast	*node;
	t_ast	*pipe_node;

	node = parse_term(current, all_data);
	while (*current && (*current)->type == TKN_PIPE)
	{
		pipe_node = create_ast_node(NODE_PIPE);
		(*current) = (*current)->next;
		pipe_node->left = node;
		pipe_node->right = parse_term(current, all_data);
		node = pipe_node;
	}
	return (node);
}
