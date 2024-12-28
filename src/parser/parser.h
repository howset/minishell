/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:23:52 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/29 00:18:00 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Function declarations and necessary includes go here
# include "../minishell.h"

// ast.c functions
t_ast		*create_ast_node(t_nodetype type);
void		print_indentation(int level, int spaces);
void		print_redirection_info(t_ast *node, int level);
void		print_node_info(t_ast *node, int level);
void		print_ast(t_ast *node, int level);

// parser_utils.c functions
void		consume_token(t_token **current);
t_tkntype	get_token_type(t_token **current);
void		parse_error(const char *message, t_token *token);
void		syntax_error(const char *message);
void		syntax_error_at(int position, const char *message);
// parser.c functions
t_ast		*parse_command(t_token **current, t_alldata *all_data);
t_ast		*parse_factor(t_token **current, t_alldata *all_data);
t_ast		*parse_term(t_token **current, t_alldata *all_data);
t_ast		*parse_pipe(t_token **current, t_alldata *all_data);
t_ast		*parse_expression(t_token **current, t_alldata *all_data);
t_ast		*parse(t_token *tokens, t_alldata *all_data);
void		syntax_error(const char *message);
void		syntax_error_at(int position, const char *message);
void		free_ast(t_ast *ast);
#endif // PARSER_H
