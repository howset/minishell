/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:52:20 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 11:36:25 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

/**This function creates a node for the list. The node is malloc'ed. The value
 * is also malloc'ed because the size changes.
 * 		Takes a defined type as the parameter
 */
t_token	*create_tkn(t_tkntype type, const char *start, int len, int pos)
{
	t_token	*token;

	token = malloc_perex(sizeof(t_token), "Malloc error on create_tkn");
	token->type = type;
	token->value = malloc_perex(len + 1, "Malloc error on create_tkn val");
	ft_strlcpy(token->value, start, len + 1);
	token->position = pos;
	token->next = NULL;
	return (token);
}

/**Add a new node to the list.
 *
 */
void	append_tkn(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

// direct copy
void	free_tkn(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
