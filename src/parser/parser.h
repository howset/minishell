#ifndef PARSER_H
# define PARSER_H

#include "../includes.h"

ASTNode *create_ast_node(NodeType type, const char *value);
t_token *advance(Parser *parser);
t_token *peek(Parser *parser);
ASTNode *parse_command(Parser *parser);
ASTNode *parse_pipeline(Parser *parser);
ASTNode *parse_redirect(Parser *parser, ASTNode *command);
ASTNode *parse(Parser *parser);
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node);

#endif