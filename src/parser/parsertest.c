#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_command {
	char **args;			//array of words
	char *input_file;		//input redir
	char *output_file;		//output redir
	int append;				//flag (0=overwrite, 1=append)
	struct s_command *next; //next node/command
} t_command;

char **tokenize(char *input) {
    char **tokens = malloc(1024 * sizeof(char *));
    char *token;
    int i = 0;

    token = strtok(input, " \t\n");
    while (token != NULL) {
        tokens[i++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;
    return tokens;
}

t_command *parse_tokens(char **tokens) 
{
	t_command *head = NULL, *current = NULL;
	char *input_file = NULL;
	char *output_file = NULL;
	int append = 0;

	while (*tokens) {
		if (strcmp(*tokens, "|") == 0) {
			// Handle pipeline: move to the next command
			//current->next = malloc(sizeof(t_command));
			//current = current->next;
			if (current == NULL) {
                current = malloc(sizeof(t_command));
                head = current;
            } else {
                current->next = malloc(sizeof(t_command));
                current = current->next;
            }
			current->args = NULL;
			current->input_file = NULL;
			current->output_file = NULL;
			current->append = 0;
			current->next = NULL;
		} else if (strcmp(*tokens, "<") == 0) {
			// Handle input redirection
			tokens++;
			current->input_file = strdup(*tokens);
		} else if (strcmp(*tokens, ">") == 0) {
			// Handle output redirection (overwrite)
			tokens++;
			current->output_file = strdup(*tokens);
			current->append = 0;
		} else if (strcmp(*tokens, ">>") == 0) {
			// Handle output redirection (append)
			tokens++;
			current->output_file = strdup(*tokens);
			current->append = 1;
		} else {
			// Handle arguments
			int argc = 0;
			while (tokens[argc] && strcmp(tokens[argc], "|") != 0 && strcmp(tokens[argc], "<") != 0 &&
				   strcmp(tokens[argc], ">") != 0 && strcmp(tokens[argc], ">>") != 0) {
				argc++;
			}
			current->args = malloc((argc + 1) * sizeof(char *));
			for (int i = 0; i < argc; i++) {
				current->args[i] = strdup(tokens[i]);
			}
			current->args[argc] = NULL;
			tokens += argc - 1; // Move to the last token processed
		}
		tokens++;
	}
	return head;
}

t_command *build_ast(char *input)
{
	char **tokens = tokenize(input);
	t_command *ast = malloc(sizeof(t_command));

	// Initialize the first command
	ast->args = NULL;
	ast->input_file = NULL;
	ast->output_file = NULL;
	ast->append = 0;
	ast->next = NULL;

	// Parse tokens
	t_command *parsed_ast = parse_tokens(tokens);

	// Free tokens
	for (int i = 0; tokens[i]; i++) free(tokens[i]);
	free(tokens);

	return parsed_ast;
}

void print_ast(t_command *ast)
{
	while (ast) {
		printf("Command: ");
		for (int i = 0; ast->args && ast->args[i]; i++) {
			printf("%s ", ast->args[i]);
		}
		printf("\n");

		if (ast->input_file) {
			printf("  Input: %s\n", ast->input_file);
		}
		if (ast->output_file) {
			printf("  Output: %s (%s)\n", ast->output_file, ast->append ? "append" : "overwrite");
		}
		ast = ast->next;
	}
}

int main() {
	char input[] = "cat file.txt | grep search > output.txt";

	// Build AST
	t_command *ast = build_ast(input);

	// Print AST
	print_ast(ast);

	return 0;
}
