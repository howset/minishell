#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	TS_L_PARENS, // (
	TS_R_PARENS, // )
	TS_A, // a
	TS_PLUS, // +
	TS_EOS, // $, end of input
	TS_INVALID, // Invalid token
	NTS_S, // S
	NTS_F // F
} t_token;

t_token lexer(char c) 
{
	switch (c) {
		case '(': return TS_L_PARENS;
		case ')': return TS_R_PARENS;
		case 'a': return TS_A;
		case '+': return TS_PLUS;
		case '\0': return TS_EOS;
		default: return TS_INVALID;
	}
}

// Main function
int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: %s '(a+a)'\n", argv[0]);
		return 1;
	}

	// Parsing table: table[non-terminal][terminal]
	int table[2][5] = {
		// NTS_S:
		{2, -1, 1, -1, -1}, // For TS_L_PARENS, TS_R_PARENS, TS_A, TS_PLUS, TS_EOS
		// NTS_F:
		{-1, -1, 3, -1, -1} // For TS_L_PARENS, TS_R_PARENS, TS_A, TS_PLUS, TS_EOS
	};

	// Stack for t_token (array-based stack)
	#define STACK_SIZE 100
	t_token stack[STACK_SIZE];
	int stack_top = 0;

	// Initialize stack with the starting t_token
	stack[stack_top++] = TS_EOS;  // Push $
	stack[stack_top++] = NTS_S;   // Push start symbol S

	// Input string pointer
	char *input = argv[1];
	char *p = input;

	// Parsing loop
	while (stack_top > 0) {
		t_token top = stack[--stack_top];  // Pop the top symbol

		// Check if the top of the stack matches the input symbol
		if (top == lexer(*p)) {
			printf("Matched symbol: %d\n", top);
			p++;  // Advance input pointer
		} else if (top >= TS_L_PARENS && top <= TS_EOS) {
			// Top of the stack is a terminal, but it doesn't match the input
			printf("Error: Unexpected token '%c'\n", *p);
			return 1;
		} else {
			// Top of the stack is a non-terminal
			int rule = table[top - NTS_S][lexer(*p)];
			if (rule == -1) {
				printf("Error: No rule for non-terminal %d with token '%c'\n", top, *p);
				return 1;
			}

			printf("Applying rule: %d\n", rule);

			// Push the t_token of the rule's production onto the stack in reverse order
			switch (rule) {
				case 1:  // S → F
					stack[stack_top++] = NTS_F;
					break;
				case 2:  // S → ( S + F )
					stack[stack_top++] = TS_R_PARENS;
					stack[stack_top++] = NTS_F;
					stack[stack_top++] = TS_PLUS;
					stack[stack_top++] = NTS_S;
					stack[stack_top++] = TS_L_PARENS;
					break;
				case 3:  // F → a
					stack[stack_top++] = TS_A;
					break;
				default:
					printf("Error: Unknown rule %d\n", rule);
					return 1;
			}
		}
	}
	if (*p == '\0') {
		printf("Finished parsing successfully!\n");
	} else {
		printf("Error: Unconsumed input '%s'\n", p);
	}
	return (0);
}
