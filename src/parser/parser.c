#include "parser.h"
//#include <string.h>

/* // Token and parser data structures
typedef enum {
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_BACKGROUND
} NodeType;

typedef struct ASTNode {
	NodeType type;
	char *value;				// Command name or operator
	struct ASTNode *left;		// Left child (e.g., for pipelines)
	struct ASTNode *right;		// Right child (e.g., for arguments or pipelines)
} ASTNode;

typedef struct {
	t_token *tokens;
	t_token *current;
} Parser; */

// Function to create a new AST node
ASTNode *create_ast_node(NodeType type, const char *value) {
	ASTNode *node = malloc(sizeof(ASTNode));
	if (!node) {
		perror("Failed to allocate AST node");
		exit(EXIT_FAILURE);
	}
	node->type = type;
	node->value = value ? strdup(value) : NULL;
	node->left = node->right = NULL;
	return node;
}

// Utility functions for parser navigation
t_token *advance(Parser *parser) {
	if (parser->current)
		parser->current = parser->current->next;
	return parser->current;
}

t_token *peek(Parser *parser) {
	return parser->current;
}

// Parsing functions
ASTNode *parse_command(Parser *parser);
ASTNode *parse_pipeline(Parser *parser);

// Parse a command (command + arguments)
ASTNode *parse_command(Parser *parser) {
	t_token *token = peek(parser);

	if (!token || token->type != TKN_WORD) {
		fprintf(stderr, "Expected command name, got %d\n", token ? token->type : TKN_INVALID);
		return NULL;
	}

	ASTNode *command_node = create_ast_node(NODE_COMMAND, token->value);
	advance(parser); // Consume command name

	ASTNode *arg_tail = NULL;
	while (peek(parser) && peek(parser)->type == TKN_WORD) {
		ASTNode *arg_node = create_ast_node(NODE_COMMAND, peek(parser)->value);
		advance(parser); // Consume argument
		if (!arg_tail) {
			command_node->right = arg_node; // First argument
			arg_tail = arg_node;
		} else {
			arg_tail->right = arg_node; // Chain additional arguments
			arg_tail = arg_node;
		}
	}

	return command_node;
}

// Parse a pipeline (command | command ...)
ASTNode *parse_pipeline(Parser *parser) {
	ASTNode *left = parse_command(parser);
	if (!left) return NULL;

	while (peek(parser) && peek(parser)->type == TKN_PIPE) {
		advance(parser); // Consume '|'
		ASTNode *right = parse_command(parser);
		if (!right) {
			fprintf(stderr, "Expected command after pipe\n");
			return NULL;
		}

		ASTNode *pipe_node = create_ast_node(NODE_PIPE, "|");
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node; // Chain pipelines
	}

	return left;
}

// Parse input redirections or background operators
ASTNode *parse_redirect(Parser *parser, ASTNode *command) {
	while (peek(parser)) {
		if (peek(parser)->type == TKN_RDIR_IN) {
			advance(parser);
			if (!peek(parser) || peek(parser)->type != TKN_WORD) {
				fprintf(stderr, "Expected file after '<'\n");
				return NULL;
			}
			ASTNode *redirect_node = create_ast_node(NODE_REDIRECT_IN, peek(parser)->value);
			redirect_node->left = command;
			advance(parser); // Consume filename
			command = redirect_node;
		} else if (peek(parser)->type == TKN_RDIR_OUT) {
			advance(parser);
			if (!peek(parser) || peek(parser)->type != TKN_WORD) {
				fprintf(stderr, "Expected file after '>'\n");
				return NULL;
			}
			ASTNode *redirect_node = create_ast_node(NODE_REDIRECT_OUT, peek(parser)->value);
			redirect_node->left = command;
			advance(parser); // Consume filename
			command = redirect_node;
		} else if (peek(parser)->type == TKN_BG) {
			advance(parser); // Consume '&'
			ASTNode *background_node = create_ast_node(NODE_BACKGROUND, "&");
			background_node->left = command;
			command = background_node;
		} else {
			break; // No more redirections or background operators
		}
	}
	return command;
}

// Top-level parser
ASTNode *parse(Parser *parser) {
	ASTNode *tree = parse_pipeline(parser);
	return parse_redirect(parser, tree);
}

// Utility functions to print and free the AST
void print_ast(ASTNode *node, int depth) {
	if (!node) return;
	for (int i = 0; i < depth; i++) printf("  ");
	printf("Node: %d, Value: %s\n", node->type, node->value);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

void free_ast(ASTNode *node) {
	if (!node) return;
	free_ast(node->left);
	free_ast(node->right);
	free(node->value);
	free(node);
}

/* // Example usage
int main() {
	const char *input = "cat file.txt | grep search > output.txt";
	t_token *tokens = lexer(input);

	Parser parser = {tokens, tokens};
	ASTNode *tree = parse(&parser);

	printf("Abstract Syntax Tree:\n");
	print_ast(tree, 0);

	free_ast(tree);
	free_tkn(tokens);
	return 0;
}
 */