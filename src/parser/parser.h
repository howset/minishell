#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

/* ASTNode *create_ast_node(NodeType type, const char *value);
t_token *advance(Parser *parser);
t_token *peek(Parser *parser);
ASTNode *parse_command(Parser *parser);
ASTNode *parse_pipeline(Parser *parser);
ASTNode *parse_redirect(Parser *parser, ASTNode *command);
ASTNode *parse(Parser *parser);
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node); */

t_command *parse_tokens(char **tokens);
t_command *build_ast(char *input);
void print_ast(t_command *ast);

#endif