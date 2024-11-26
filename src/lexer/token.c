#include "lexer.h"

/**This function creates a node for the list. The node is malloc'ed. The value
 * is also malloc'ed because the size changes.
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
		// new_token->prev = temp; //doubly linked
	}
}

// direct copy
void	print_tkn(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Type: %d, Value: '%s', Position: %d\n", current->type,
			current->value, current->position);
		current = current->next;
	}
}

// direct copy
void	free_tkn(t_token *tokens)
{
	t_token *current = tokens;
	while (current)
	{
		t_token *next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}