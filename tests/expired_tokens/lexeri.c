#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <bsd/string.h>

#define MAX_TOKENS 100 // Set a limit on the number of tokens

typedef enum e_tkntype
{
    TKN_WORD,
    TKN_METACHAR,
}   t_tkntype;

typedef struct s_token {
    t_tkntype type;
    char *value;  // In this version, we still need to store a pointer to the value
}   t_token;

// Lexer function
t_token *lexer(const char *input, int *token_count) {
    size_t i = 0;
    size_t start;
    size_t length;
    
    static t_token tokens[MAX_TOKENS]; // Static array for tokens
    *token_count = 0;

    while (input[i] != '\0') {
        if (isspace(input[i])) {
            i++; // Skip whitespace
            continue;
        }

        t_token token;  // Temporary token

        // If it's a word (alphanumeric characters)
        if (isalnum(input[i])) {
            start = i;
            while (isalnum(input[i])) i++;
            length = i - start;
            
            token.type = TKN_WORD;
            token.value = malloc(length + 1);  // Allocate space for the word value
            if (!token.value) {
                perror("Malloc failed for token.value (words)");
                exit(EXIT_FAILURE);
            }
            strlcpy(token.value, &input[start], length + 1);
        }
        // If it's a metacharacter (like '>', '<', '|', etc.)
        else {
            start = i;
            if (input[i] == '<' && input[i + 1] == '<') {
                i += 2;  // Handle '<<'
            } else if (input[i] == '>' && input[i + 1] == '>') {
                i += 2;  // Handle '>>'
            } else {
                i++; // Handle single-character metacharacters
            }

            length = i - start;
            token.type = TKN_METACHAR;
            token.value = malloc(length + 1);  // Allocate space for metacharacter value
            if (!token.value) {
                perror("Malloc failed for token.value (metachars)");
                exit(EXIT_FAILURE);
            }
            strlcpy(token.value, &input[start], length + 1);
        }

        // Add the token to the tokens array if there's space
        if (*token_count < MAX_TOKENS) {
            tokens[*token_count] = token;
            (*token_count)++;
        } else {
            printf("Warning: Too many tokens, truncating.\n");
            free(token.value);  // Free the extra token
            break;
        }
    }

    return tokens;
}

void free_tokens(t_token *tokens, size_t token_count) {
    for (size_t i = 0; i < token_count; i++) {
        free(tokens[i].value);  // Free the dynamically allocated values
    }
}

void print_tokens(t_token *tokens, size_t token_count) {
    for (size_t i = 0; i < token_count; i++) {
        printf("Token %zu: ", i + 1);
        if (tokens[i].type == TKN_WORD) {
            printf("WORD, ");
        } else {
            printf("METACHARACTER, ");
        }
        printf("Value: '%s'\n", tokens[i].value);
    }
}

int main(void) {
    char *input;
    t_token *tokens;
    int token_count;

    while (1) {
        input = readline("wtf-shell> ");
        if (!input) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        add_history(input); // add input to readline history

        if (strncmp(input, "exit", 4) == 0) {
            free(input);  // Free the input
            break;
        }

        tokens = lexer(input, &token_count);
        print_tokens(tokens, token_count);
        free_tokens(tokens, token_count);  // Free the tokens
        free(input);  // Free the input string
    }

    return 0;
}
