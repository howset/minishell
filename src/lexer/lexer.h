/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:53:27 by reldahli          #+#    #+#             */
/*   Updated: 2024/11/29 12:58:54 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

// lexer.c
t_token				*lexer(const char *input);
int					handle_token(const char *input, int pos, t_token **tokens);

// token.c
t_token				*create_tkn(t_tkntype type, const char *start, int len,
						int pos);
void				append_tkn(t_token **head, t_token *new_token);
void				print_tkn(t_token *tokens);
void				free_tkn(t_token *tokens);

// operator.c
int					lex_or_pipe(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);
int					lex_and_bg(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);
int					lex_semi_col(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);

// redirection.c
int					lex_hd_rin(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);
int					lex_app_rout(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);

// grouping.c
int					lex_paren_op(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);
int					lex_paren_cl(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);

// quote.c
int					lex_quo_sin(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);
int					lex_quo_dou(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);

// word.c
int					lex_var(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);
// int lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn);
int					lex_word(const char *input, int pos, t_token **tokens,
						t_token *new_tkn);
// int lex_word(const char *input, int pos, t_token **tokens);

#endif
