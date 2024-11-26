#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the token types
typedef enum e_token_type {
    TOKEN_WORD,            // 0 Generic word (commands, filenames, etc.)
    TOKEN_PIPE,            // 1 |
    TOKEN_REDIRECT_IN,     // 2 <
    TOKEN_REDIRECT_OUT,    // 3 >
    TOKEN_REDIRECT_APPEND, // 4 >>
    TOKEN_HEREDOC,         // 5 <<
    TOKEN_BACKGROUND,      // 6 &
    TOKEN_AND,             // 7 &&
    TOKEN_OR,              // 8 ||
    TOKEN_SEMICOLON,       // 9 ;
    TOKEN_OPEN_PAREN,      // 10 (
    TOKEN_CLOSE_PAREN,     // 11 )
    TOKEN_VARIABLE,        // 12 $VAR
    TOKEN_QUOTE_SINGLE,    // 13 '
    TOKEN_QUOTE_DOUBLE,    // 14 "
    TOKEN_EOF              // 15 End of input
} t_token_type;

// Define the token structure
typedef struct s_token {
    t_token_type     type;     // Type of the token
    char            *value;    // String value of the token
    int              position; // Position in the input string
    struct s_token  *next;     // Pointer to the next token
} t_token;

// Function to create a new token
t_token *create_token(t_token_type type, const char *start, int length, int position) {
    t_token *token = malloc(sizeof(t_token));
    if (!token) {
        perror("Failed to allocate memory for token");
        exit(EXIT_FAILURE);
    }

    token->type = type;
    token->value = strndup(start, length); // Duplicate the token value
    if (!token->value) {
        perror("Failed to allocate memory for token value");
        free(token);
        exit(EXIT_FAILURE);
    }
    token->position = position;
    token->next = NULL;

    return token;
}

// Function to append a token to the linked list
void append_token(t_token **head, t_token *new_token) {
    if (!*head) {
        *head = new_token;
    } else {
        t_token *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
}

// The lexer function to tokenize the input string
t_token *tokenize_input(const char *input) {
    t_token *tokens = NULL; // Head of the linked list
    int position = 0;       // Current position in the input string

    while (input[position]) {
        // Skip whitespace
        if (isspace(input[position])) {
            position++;
            continue;
        }

        // Handle different token types
        if (input[position] == '|') {
            if (input[position + 1] == '|') {
                // TOKEN_OR
                t_token *token = create_token(TOKEN_OR, &input[position], 2, position);
                append_token(&tokens, token);
                position += 2;
            } else {
                // TOKEN_PIPE
                t_token *token = create_token(TOKEN_PIPE, &input[position], 1, position);
                append_token(&tokens, token);
                position++;
            }
        } else if (input[position] == '&') {
            if (input[position + 1] == '&') {
                // TOKEN_AND
                t_token *token = create_token(TOKEN_AND, &input[position], 2, position);
                append_token(&tokens, token);
                position += 2;
            } else {
                // TOKEN_BACKGROUND
                t_token *token = create_token(TOKEN_BACKGROUND, &input[position], 1, position);
                append_token(&tokens, token);
                position++;
            }
        } else if (input[position] == '>') {
            if (input[position + 1] == '>') {
                // TOKEN_REDIRECT_APPEND
                t_token *token = create_token(TOKEN_REDIRECT_APPEND, &input[position], 2, position);
                append_token(&tokens, token);
                position += 2;
            } else {
                // TOKEN_REDIRECT_OUT
                t_token *token = create_token(TOKEN_REDIRECT_OUT, &input[position], 1, position);
                append_token(&tokens, token);
                position++;
            }
        } else if (input[position] == '<') {
            if (input[position + 1] == '<') {
                // TOKEN_HEREDOC
                t_token *token = create_token(TOKEN_HEREDOC, &input[position], 2, position);
                append_token(&tokens, token);
                position += 2;
            } else {
                // TOKEN_REDIRECT_IN
                t_token *token = create_token(TOKEN_REDIRECT_IN, &input[position], 1, position);
                append_token(&tokens, token);
                position++;
            }
        } else if (input[position] == ';') {
            // TOKEN_SEMICOLON
            t_token *token = create_token(TOKEN_SEMICOLON, &input[position], 1, position);
            append_token(&tokens, token);
            position++;
        } else if (input[position] == '(') {
            // TOKEN_OPEN_PAREN
            t_token *token = create_token(TOKEN_OPEN_PAREN, &input[position], 1, position);
            append_token(&tokens, token);
            position++;
        } else if (input[position] == ')') {
            // TOKEN_CLOSE_PAREN
            t_token *token = create_token(TOKEN_CLOSE_PAREN, &input[position], 1, position);
            (current);
        current = next;
    }
}

// Example usage
int main() {
    const char *input = "  cat file.txt | grep \"search term\" > output.txt";
    t_token *tokens = tokenize_input(input);
    print_tokens(tokens);
    free_tokens(tokens);
    return 0;
}
append_token(&tokens, token);
            position++;
        } else if (input[position] == '$') {
            // TOKEN_VARIABLE
            int start = position;
            position++; // Skip the '$'
            while (isalnum(input[position]) || input[position] == '_') {
                position++;
            }
            int length = position - start;
            t_token *token = create_token(TOKEN_VARIABLE, &input[start], length, start);
            append_token(&tokens, token);
        } else if (input[position] == '\'') {
            // TOKEN_QUOTE_SINGLE
            int start = position;
            position++; // Skip the opening quote
            while (input[position] && input[position] != '\'') {
                position++;
            }
            if (input[position] == '\'') {
                position++; // Skip the closing quote
                int length = position - start;
                t_token *token = create_token(TOKEN_QUOTE_SINGLE, &input[start], length, start);
                append_token(&tokens, token);
            } else {
                fprintf(stderr, "Error: Unterminated single quote at position %d\n", start);
                exit(EXIT_FAILURE);
            }
        } else if (input[position] == '"') {
            // TOKEN_QUOTE_DOUBLE
            int start = position;
            position++; // Skip the opening quote
            while (input[position] && input[position] != '"') {
                position++;
            }
            if (input[position] == '"') {
                position++; // Skip the closing quote
                int length = position - start;
                t_token *token = create_token(TOKEN_QUOTE_DOUBLE, &input[start], length, start);
                append_token(&tokens, token);
            } else {
                fprintf(stderr, "Error: Unterminated double quote at position %d\n", start);
                exit(EXIT_FAILURE);
            }
        } else {
            // TOKEN_WORD
            int start = position;
            while (input[position] && !isspace(input[position]) &&
                   !strchr("|&;<>$()'\"", input[position])) {
                position++;
            }
            int length = position - start;
            t_token *token = create_token(TOKEN_WORD, &input[start], length, start);
            append_token(&tokens, token);
        }
    }

    return tokens;
}

// Function to print the tokens (for debugging purposes)
void print_tokens(t_token *tokens) {
    t_token *current = tokens;
    while (current) {
        printf("Type: %d, Value: '%s', Position: %d\n",
               current->type, current->value, current->position);
        current = current->next;
    }
}

// Function to free the tokens
void free_tokens(t_token *tokens) {
    t_token *current = tokens;
    while (current) {
        t_token *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

// Example usage
int main() {
    const char *input = "  cat file.txt | grep \"search term\" > output.txt";
    t_token *tokens = tokenize_input(input);
    print_tokens(tokens);
    free_tokens(tokens);
    return 0;
}
