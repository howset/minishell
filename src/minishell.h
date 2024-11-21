/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:08:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/21 18:46:55 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/src/ft_printf/ft_printf.h"
# include "./lib/src/get_next_line/get_next_line.h"
# include "./lib/src/libft/libft.h"

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* typedef enum {
	TOKEN_COMMANDS, //0 Token command
	TOKEN_ARGUMENTS, //1 --> anything
	TOKEN_REDIRECTIONS, //2 Token redirection
	TOKEN_END //3
} TokenType;
 */
/* typedef enum e_tkntype{
	TKN_WORD, //everything (incl keywords, commands, others)
	TKN_METACHAR, //separator e.g. |, &, ;, (, ), <, >, space, tab, newline
	TKN_OPERATOR,
	TKN_END,
}	t_tkntype; */

#define ARG_LEN 100 //arrange by argc??

typedef enum e_tkntype
{
	TKN_WORD,
	TKN_METACHAR,
}	t_tkntype;

typedef struct s_token{
	t_tkntype	type;
	char		*value;
}	t_token;

int	ft_isspace(char c);
//void	lexer(const char *input, Token tokens[], int *token_count) ;
t_token *lexer(const char *input, int *token_count);
void free_tokens(t_token *tokens, size_t token_count);

#endif