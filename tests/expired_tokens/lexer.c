#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    char value[256];
} Token;

void lexer(const char *input, Token tokens[], int *token_count) {
    const char *current = input;
    int count = 0;

    while (*current != '\0') {
        // Skip whitespace
        while (isspace(*current)) current++;

        if (isalpha(*current)) { // Identifier
            int length = 0;
            while (isalnum(*current)) {
                tokens[count].value[length++] = *current++;
            }
            tokens[count].value[length] = '\0';
            tokens[count].type = TOKEN_IDENTIFIER;
            count++;
        } else if (isdigit(*current)) { // Number
            int length = 0;
            while (isdigit(*current)) {
                tokens[count].value[length++] = *current++;
            }
            tokens[count].value[length] = '\0';
            tokens[count].type = TOKEN_NUMBER;
            count++;
        } else if (*current == '|' || *current == '-' || *current == '*' || *current == '/') { // Operator
            tokens[count].value[0] = *current++;
            tokens[count].value[1] = '\0';
            tokens[count].type = TOKEN_OPERATOR;
            count++;
        } else { // Unknown character, skip
            current++;
        }
    }

    // End token
    tokens[count].type = TOKEN_END;
    strcpy(tokens[count].value, "END");
    count++;

    *token_count = count;
}

int main() {
    char input[256];
    printf("Enter a command: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character
    input[strcspn(input, "\n")] = '\0';

    Token tokens[256];
    int token_count = 0;

    lexer(input, tokens, &token_count);

    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("Token count:%d, Type: %d, Value: %s\n", token_count, tokens[i].type, tokens[i].value);
    }

    return 0;
}