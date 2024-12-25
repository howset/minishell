/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:23:52 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/25 12:10:16 by reldahli         ###   ########.fr       */
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
// comm_table_utils.c functions
t_simcomm	*create_simcomm(t_ast *node);
int			traverse_ast(t_ast *node, t_commtab *table);
int			handle_redirection_node(t_ast *node, t_commtab *table);
int			handle_compound_nodes(t_ast *node, t_commtab *table);
// comm_table.c functions
t_commtab	*ast_to_commtab(t_ast *root);
t_commtab	*create_commtab(void);
int			handle_command_node(t_ast *node, t_commtab *table);
void		print_commtab(t_commtab *table);
// parser_utils.c functions
void		consume_token(t_token **current);
t_tkntype	get_token_type(t_token **current);
void		parse_error(const char *message, t_token *token);
void		syntax_error(const char *message);
void		syntax_error_at(int position, const char *message);
// parser.c functions
t_ast		*parse_command(t_token **current);
t_ast		*parse_factor(t_token **current);
t_ast		*parse_term(t_token **current);
t_ast		*parse_pipe(t_token **current);
t_ast		*parse_expression(t_token **current);
t_ast		*parse(t_token *tokens);
void		syntax_error(const char *message);
void		syntax_error_at(int position, const char *message);
void		free_ast(t_ast *ast);
#endif // PARSER_H
