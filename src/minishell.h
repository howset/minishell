/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:08:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/25 16:46:57 by hsetyamu         ###   ########.fr       */
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

typedef enum e_tkntype
{
	TKN_OR,
	TKN_PIPE,
	TKN_BG,
	TKN_AND,
	TKN_RDIR_IN,
	TKN_HEREDOC,
	TKN_RDIR_OUT,
	TKN_APPEND,
	TKN_SEMCOL,
	TKN_PAREN_OP,
	TKN_PAREN_CL,
	TKN_QUO_SIN,
	TKN_QUO_DOU,
	TKN_VAR,
	TKN_WORD,
	TKN_EOF,
}	t_tkntype;

typedef struct s_token{
	t_tkntype		type;
	char			*value;
	int				position;
	struct s_token	*next;
	//struct s_token	*prev; //doubly linked
}	t_token;

//lexer.c
t_token	*lexer(const char *input);
t_token	*create_tkn(t_tkntype type, const char *start, int len, int pos);
void	append_tkn(t_token **head, t_token *new_token);
void	print_tkn(t_token *tokens);
void	free_tkn(t_token *tokens);

//lexer_utils1.c
int lex_or_pipe(const char *input, int pos, t_token *tokens, t_token *new_tkn);
int lex_and_bg(const char *input, int pos, t_token *tokens, t_token *new_tkn);
int lex_hd_rin(const char *input, int pos, t_token *tokens, t_token *new_tkn);
int lex_app_rout(const char *input, int pos, t_token *tokens, t_token *new_tkn);
int lex_single_sym(const char *input, int pos, t_token *tokens, t_token *new_tkn);

//lexer_utils2.c
int lex_quo_sin(const char *input, int pos, t_token *tokens, t_token *new_tkn);
int lex_quo_dou(const char *input, int pos, t_token *tokens, t_token *new_tkn);
int lex_var(const char *input, int pos, t_token *tokens, t_token *new_tkn);
int lex_word(const char *input, int pos, t_token *tokens, t_token *new_tkn);

//utils_wrapper.c
void	*malloc_perex(size_t bytes, char *msg);

#endif