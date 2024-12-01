#ifndef PARSER_H
# define PARSER_H

// Function declarations and necessary includes go here
# include "../minishell.h"

t_ast	*create_ast_node(t_nodetype type);
t_ast	*parse_command(t_token **current);
t_ast	*parse_factor(t_token **current);
t_ast	*parse_term(t_token **current);
t_ast	*parse_pipe(t_token **current);
t_ast	*parse_expression(t_token **current);
t_ast	*parse(t_token *tokens);
t_ast	*create_ast_node(t_nodetype type);
void	print_ast(t_ast *node, int level);
void	syntax_error(const char *message);
void syntax_error_at(int position, const char *message);
#endif // PARSER_H
