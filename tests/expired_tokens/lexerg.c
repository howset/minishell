#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_METACHARACTER,
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token *lexer(const char *input, size_t *token_count) {
    size_t capacity = 10; // Initial capacity for tokens
    Token *tokens = malloc(sizeof(Token) * capacity);
    if (!tokens) {
        perror("Failed to allocate memory for tokens");
        exit(EXIT_FAILURE);
    }

    *token_count = 0;
    size_t i = 0;

    while (input[i] != '\0') {
        // Skip whitespace
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // Expand token array if needed
        if (*token_count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, sizeof(Token) * capacity);
            if (!tokens) {
                perror("Failed to reallocate memory for tokens");
                exit(EXIT_FAILURE);
            }
        }

        Token token;
        if (isalnum(input[i]) || input[i] == '_') {
            // Start of a WORD token
            size_t start = i;
            while (isalnum(input[i]) || input[i] == '_') {
                i++;
            }

            size_t length = i - start;
            token.type = TOKEN_WORD;
            token.value = malloc(length + 1);
            if (!token.value) {
                perror("Failed to allocate memory for token value");
                exit(EXIT_FAILURE);
            }
            strncpy(token.value, &input[start], length);
            token.value[length] = '\0';
        } else {
            // Start of a METACHARACTER token
            size_t start = i;

            // Handle specific metacharacter sequences
            if (input[i] == '<' && input[i + 1] == '<') {
                i += 2; // Handle '<<' as a single token
            } else if (input[i] == '>' && input[i + 1] == '>') {
                i += 2; // Handle '>>' as a single token
            } else if (input[i] == '&') {
                i += 1; // Handle '&' as a single token
            } else {
                i++; // Handle single-character metacharacters (e.g., '|', '<', '>')
            }

            size_t length = i - start;
            token.type = TOKEN_METACHARACTER;
            token.value = malloc(length + 1);
            if (!token.value) {
                perror("Failed to allocate memory for token value");
                exit(EXIT_FAILURE);
            }
            strncpy(token.value, &input[start], length);
            token.value[length] = '\0';
        }

        // Add the token to the array
        tokens[*token_count] = token;
        (*token_count)++;
    }

    return tokens;
}

void print_tokens(Token *tokens, size_t token_count) {
    for (size_t i = 0; i < token_count; i++) {
        printf("Token %zu: ", i + 1);
        if (tokens[i].type == TOKEN_WORD) {
            printf("WORD, ");
        } else {
            printf("METACHARACTER, ");
        }
        printf("Value: '%s'\n", tokens[i].value);
    }
}

void free_tokens(Token *tokens, size_t token_count) {
    for (size_t i = 0; i < token_count; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}

int main() {
    const char *input = "echo hello << input.txt >> output.txt & | grep test";
    size_t token_count = 0;

    Token *tokens = lexer(input, &token_count);
    print_tokens(tokens, token_count);
    free_tokens(tokens, token_count);

    return 0;
}
