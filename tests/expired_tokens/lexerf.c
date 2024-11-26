#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_OPERATOR,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_BACKGROUND,
    TOKEN_END_OF_INPUT
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

// Function to create a token
Token create_token(TokenType type, const char *value) {
    Token token;
    token.type = type;
    token.value = strdup(value); // Allocate memory for value
    return token;
}

// Function to free a token
void free_token(Token token) {
    free(token.value);
}

// Function to print a token
void print_token(Token token) {
    printf("Token Type: ");
    switch (token.type) {
        case TOKEN_WORD:
            printf("WORD");
            break;
        case TOKEN_OPERATOR:
            printf("OPERATOR");
            break;
        case TOKEN_PIPE:
            printf("PIPE");
            break;
        case TOKEN_REDIRECT_IN:
            printf("REDIRECT_IN");
            break;
        case TOKEN_REDIRECT_OUT:
            printf("REDIRECT_OUT");
            break;
        case TOKEN_BACKGROUND:
            printf("BACKGROUND");
            break;
        case TOKEN_END_OF_INPUT:
            printf("END_OF_INPUT");
            break;
    }
    printf(", Value: '%s'\n", token.value);
}

// Lexer function
Token *lexer(const char *input, int *token_count) {
    int index = 0;
    int input_length = strlen(input);
    int capacity = 10;
    *token_count = 0;

    Token *tokens = malloc(sizeof(Token) * capacity);

    while (index < input_length) {
        // Skip whitespace
        while (index < input_length && isspace(input[index])) {
            index++;
        }
        if (index >= input_length) {
            break;
        }

        // Check for special characters
        if (input[index] == '|') {
            tokens[(*token_count)++] = create_token(TOKEN_PIPE, "|");
            index++;
        } else if (input[index] == '>') {
            tokens[(*token_count)++] = create_token(TOKEN_REDIRECT_OUT, ">");
            index++;
        } else if (input[index] == '<') {
            tokens[(*token_count)++] = create_token(TOKEN_REDIRECT_IN, "<");
            index++;
        } else if (input[index] == '&') {
            tokens[(*token_count)++] = create_token(TOKEN_BACKGROUND, "&");
            index++;
        } else {
            // Handle words (commands or arguments)
            char buffer[256];
            int buffer_index = 0;

            while (index < input_length && !isspace(input[index]) &&
                   input[index] != '|' && input[index] != '>' &&
                   input[index] != '<' && input[index] != '&') {
                buffer[buffer_index++] = input[index++];
            }
            buffer[buffer_index] = '\0';
            tokens[(*token_count)++] = create_token(TOKEN_WORD, buffer);
        }

        // Expand token array if necessary
        if (*token_count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, sizeof(Token) * capacity);
        }
    }

    // Add end-of-input token
    tokens[(*token_count)++] = create_token(TOKEN_END_OF_INPUT, "");

    return tokens;
}

// Main function to test the lexer
int main() {
    const char *command = "echo hello | grep 'world' > output.txt &";
    int token_count = 0;

    Token *tokens = lexer(command, &token_count);

    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        print_token(tokens[i]);
        free_token(tokens[i]); // Free each token after use
    }

    free(tokens); // Free the token array

    return 0;
}
