/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:57:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/25 15:25:42 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(const char *input);
t_token	*create_tkn(t_tkntype type, const char *start, int len, int pos);
void	append_tkn(t_token **head, t_token *new_token); //ft_lstadd_back??
void	print_tkn(t_token *tokens);
void	free_tkn(t_token *tokens);

t_token	*lexer(const char *input)
{
	t_token	*tokens;
	t_token	*new_tkn;
	int		pos;
	int		start;
	int		len;
	t_token *eof_tkn;

	tokens = NULL;
	new_tkn = NULL;
	pos = 0;
	//start = 0;
	//len = 0;
	while (input[pos])
	{
		if (ft_isspace(input[pos]) == 1)
			pos++;
		if (input[pos] == '|')
		{
			if (input[pos + 1] == '|')
			{
				new_tkn = create_tkn(TKN_OR, &input[pos], 2, pos);
				append_tkn(&tokens, new_tkn);
				pos += 2;
			}
			else
			{
				new_tkn = create_tkn(TKN_PIPE, &input[pos], 1, pos);
				append_tkn(&tokens, new_tkn);
				pos++;
			}
		}
		else if (input[pos] == '&')
		{
			if (input[pos + 1] == '&')
			{
				new_tkn = create_tkn(TKN_AND, &input[pos], 2, pos);
				append_tkn(&tokens, new_tkn);
				pos += 2;
			}
			else
			{
				new_tkn = create_tkn(TKN_BG, &input[pos], 1, pos);
				append_tkn(&tokens, new_tkn);
				pos++;
			}
		}
		else if (input[pos] == '<')
		{
			if (input[pos + 1] == '<')
			{
				new_tkn = create_tkn(TKN_HEREDOC, &input[pos], 2, pos);
				append_tkn(&tokens, new_tkn);
				pos += 2;
			}
			else
			{
				new_tkn = create_tkn(TKN_RDIR_IN, &input[pos], 1, pos);
				append_tkn(&tokens, new_tkn);
				pos++;
			}
		}
		else if (input[pos] == '>')
		{
			if (input[pos + 1] == '>')
			{
				new_tkn = create_tkn(TKN_APPEND, &input[pos], 2, pos);
				append_tkn(&tokens, new_tkn);
				pos += 2;
			}
			else
			{
				new_tkn = create_tkn(TKN_RDIR_OUT, &input[pos], 1, pos);
				append_tkn(&tokens, new_tkn);
				pos++;
			}
		}
		else if (input[pos] == ';')
		{
			new_tkn = create_tkn(TKN_SEMCOL, &input[pos], 1, pos);
			append_tkn(&tokens, new_tkn);
			pos++;
		}
		else if (input[pos] == '(')
		{
			new_tkn = create_tkn(TKN_PAREN_OP, &input[pos], 1, pos);
			append_tkn(&tokens, new_tkn);
			pos++;
		}
		else if (input[pos] == ')')
		{
			new_tkn = create_tkn(TKN_PAREN_CL, &input[pos], 1, pos);
			append_tkn(&tokens, new_tkn);
			pos++;
		}
		else if (input[pos] == '\'')
		{
			start = pos;
			pos++;
			while (input[pos] && input[pos] != '\'')
				pos++;
			if (input[pos] == '\'')
			{
				pos++;
				len = pos - start;
				new_tkn = create_tkn(TKN_QUO_SIN, &input[start], len, start);
				append_tkn(&tokens, new_tkn);
			}
			else
			{
				perror("Unterminated single quote");
				exit(EXIT_FAILURE);
			}
		}
		else if (input[pos] == '"')
		{
			start = pos;
			pos++;
			while (input[pos] && input[pos] != '"')
				pos++;
			if (input[pos] == '"')
			{
				pos++;
				len = pos - start;
				new_tkn = create_tkn(TKN_QUO_DOU, &input[start], len, start);
				append_tkn(&tokens, new_tkn);
			}
			else
			{
				perror("Unterminated double quote");
				exit(EXIT_FAILURE);
			}
		}
		else if (input[pos] == '$')
		{
			start = pos;
			pos++;
			while (ft_isalnum(input[pos]) || input[pos] == '_')
				pos++;
			len = pos - start;
			new_tkn = create_tkn(TKN_VAR, &input[start], len, start);
			append_tkn(&tokens, new_tkn);
		}
		else
		{
			start = pos;
			while (input[pos] && !ft_isspace(input[pos]) &&
					!ft_strchr("|&;<>$()'\"", input[pos]))
				pos++;
			len = pos - start;
			new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
			append_tkn(&tokens, new_tkn);
		}
	}
	eof_tkn = create_tkn(TKN_EOF, "", 0, pos);
	append_tkn(&tokens, eof_tkn);
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