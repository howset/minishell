/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:23:52 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:42:13 by reldahli         ###   ########.fr       */
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
void		syntax_error_at(int position, const char *message);
char		*sanitize_text(char *text, t_alldata *all_data);
// parser.c functions
t_ast		*parse_command(t_token **current, t_alldata *all_data);
t_ast		*parse_factor(t_token **current, t_alldata *all_data);
t_ast		*parse_term(t_token **current, t_alldata *all_data);
t_ast		*parse_pipe(t_token **current, t_alldata *all_data);
t_ast		*parse_expression(t_token **current, t_alldata *all_data);
t_ast		*parse(t_token *tokens, t_alldata *all_data);
void		syntax_error_at(int position, const char *message);
void		free_ast(t_ast *ast);

// string_processing.c
char		*extract_and_process_quotes(char *result, int *i,
				t_alldata *all_data);
char		*process_double_quotes(char *result, int *i, t_alldata *all_data);
char		*process_single_quotes(char *result, int *i);
char		*process_exit_status(char *result, int *i, t_alldata *all_data);
char		*extract_var_name(const char *result, int *i, char *var_name);

// env_variable_handling.c
char		*process_env_variable(char *result, int *i, t_alldata *all_data);
char		*handle_special_char(char *result, int *i, t_alldata *all_data);
char		*sanitize_text(char *text, t_alldata *all_data);
#endif // PARSER_H
