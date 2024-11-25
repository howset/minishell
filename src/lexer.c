/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:57:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/25 18:31:03 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(const char *input);
t_token	*create_tkn(t_tkntype type, const char *start, int len, int pos);
void	append_tkn(t_token **head, t_token *new_token);
void	print_tkn(t_token *tokens);
void	free_tkn(t_token *tokens);

t_token	*lexer(const char *input)
{
	t_token	*tokens;
	t_token	*new_tkn;
	int		pos;
	int		start;
	int		len;

	tokens = NULL;
	new_tkn = NULL;
	pos = 0;
	while (input[pos])
	{
		if (ft_isspace(input[pos]))
			pos++;
		if (input[pos] == '|')
			pos = lex_or_pipe(input, pos, tokens, new_tkn);
		else if (input[pos] == '&')
			pos = lex_and_bg(input, pos, tokens, new_tkn);
		else if (input[pos] == '<')
			pos = lex_hd_rin(input, pos, tokens, new_tkn);
		else if (input[pos] == '>')
			pos = lex_app_rout(input, pos, tokens, new_tkn);
		else if (input[pos] == ';')
			pos = lex_single_sym(input, pos, tokens, new_tkn);
		else if (input[pos] == '(')
			pos = lex_single_sym(input, pos, tokens, new_tkn);
		else if (input[pos] == ')')
			pos = lex_single_sym(input, pos, tokens, new_tkn);
		else if (input[pos] == '\'')
			pos = lex_quo_sin(input, pos, tokens, new_tkn);
		else if (input[pos] == '"')
			pos = lex_quo_dou(input, pos, tokens, new_tkn);
		else if (input[pos] == '$')
			pos = lex_var(input, pos, tokens, new_tkn);
		else if (ft_isalnum(input[pos]))
			//pos = lex_word(input, pos, &tokens, new_tkn);
			//pos = lex_word(input, pos, tokens, new_tkn);
		{
			start = pos;
			while ((input[pos] && !ft_isspace(input[pos])) && 
					!ft_strchr("|&;<>$()'\"", input[pos]))
				pos++;
			len = pos - start;
			new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
			append_tkn(&tokens, new_tkn);
		}
	}
	new_tkn = create_tkn(TKN_EOF, "", 0, pos);
	append_tkn(&tokens, new_tkn);
	return (tokens);
}

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

void	append_tkn(t_token **head, t_token *new_token)
{
	t_token *temp;
	
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		//new_token->prev = temp; //doubly linked
	}
}

//direct copy
void print_tkn(t_token *tokens) 
{
	t_token *current = tokens;
	while (current) 
	{
		printf("Type: %d, Value: '%s', Position: %d\n",
				current->type, current->value, current->position);
		current = current->next;
	}
}

//direct copy
void free_tkn(t_token *tokens) 
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