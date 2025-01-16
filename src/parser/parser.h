/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:23:52 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 18:21:31 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

// ast.c functions
t_ast		*create_ast_node(t_nodetype type);
void		free_ast(t_ast *ast);

// parser_utils.c functions
void		consume_token(t_token **current);
t_tkntype	get_token_type(t_token **current);
void		parse_error(const char *message, t_token *token);
void		syntax_error_at(int position, const char *message);

// parser.c functions
int			is_argument_token(t_tkntype type);
int			is_redirection_token(t_tkntype type);
t_ast		*parser(t_token *tokens, t_alldata *all_data);

// parse_expression.c
t_ast		*parse_expression(t_token **current, t_alldata *all_data);
t_nodetype	check_optype(t_tkntype token_type);
t_ast		*handle_opnode(t_token **current, t_alldata *all_data, 
				t_ast *left_node, t_nodetype type);

// parse_pipe.c
t_ast		*parse_pipe(t_token **current, t_alldata *all_data);

// parse_term.c
t_ast		*parse_term(t_token **current, t_alldata *all_data);
int			handle_redir(t_token **current, t_alldata *all_data, t_ast **node);
int			check_redirtarget(t_token **current);
int			handle_arg(t_token **current, t_alldata *all_data, t_ast *node);

// parse_factor.c
t_ast		*parse_factor(t_token **current, t_alldata *all_data);

// parse_command.c
t_ast		*parse_command(t_token **current, t_alldata *all_data);
int			process_tkn(t_token **current, t_ast *node, t_alldata *all_data);

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
