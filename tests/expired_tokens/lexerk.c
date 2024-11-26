#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token type definitions
typedef enum e_tkntype {
    TKN_OR,
    TKN_PIPE,
    TKN_BG,
    TKN_AND,
    TKN_RDIR_IN,
    TKN_HEREDOC,
    TKN_RDIR_OUT,
    TKN_APPEND,
    TKN_SEMCOL,
    TKN_PAREN_OP,
    TKN_PAREN_CL,
    TKN_QUO_SIN,
    TKN_QUO_DOU,
    TKN_VAR,
    TKN_WORD,
    TKN_EOF,
} t_tkntype;

// Token structure
typedef struct s_token {
    t_tkntype   type;
    char        *value;
    int         position;
    struct s_token *next;
} t_token;

// Function prototypes
t_token *lexer(const char *input);
t_token *create_tkn(t_tkntype type, const char *start, int len, int pos);
void append_tkn(t_token **head, t_token *new_token);
void print_tkn(t_token *tokens);
void free_tkn(t_token *tokens);
int lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn);


int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	res;

	res = 0;
	if (size == 0)
	{
		while (src[res])
			res++;
		return (res);
	}
	while (res < size -1 && src[res] != '\0')
	{
		dst[res] = src[res];
		res++;
	}
	if (res < size)
		dst[res] = '\0';
	while (src[res] != '\0')
		res++;
	return (res);
}

int	ft_isalnum(int i)
{
	if (('a' <= i && i <= 'z')
		|| ('A' <= i && i <= 'Z')
		|| ('0' <= i && i <= '9'))
		return (1);
	return (0);
}

int lex_or_pipe(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '|')
	{
		new_tkn = create_tkn(TKN_OR, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_PIPE, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_and_bg(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '&')
	{
		new_tkn = create_tkn(TKN_AND, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_BG, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_hd_rin(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '<')
	{
		new_tkn = create_tkn(TKN_HEREDOC, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_IN, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_app_rout(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '>')
	{
		new_tkn = create_tkn(TKN_APPEND, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_OUT, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_single_sym(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos] == ';')
	{
		new_tkn = create_tkn(TKN_SEMCOL, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	else if (input[pos] == '(')
	{
		new_tkn = create_tkn(TKN_PAREN_OP, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	else if (input[pos] == ')')
	{
		new_tkn = create_tkn(TKN_PAREN_CL, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_quo_sin(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (input[pos] && input[pos] != '\'')
		pos++;
	if (input[pos] == '\'')
	{
		pos++;
		len = pos - start;
		new_tkn = create_tkn(TKN_QUO_SIN, &input[start], len, start);
		append_tkn(&tokens, new_tkn);
	}
	else
	{
		perror("Unterminated single quote");
		exit(EXIT_FAILURE);
	}
	return (pos);
}

int lex_quo_dou(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (input[pos] && input[pos] != '"')
		pos++;
	if (input[pos] == '"')
	{
		pos++;
		len = pos - start;
		new_tkn = create_tkn(TKN_QUO_DOU, &input[start], len, start);
		append_tkn(&tokens, new_tkn);
	}
	else
	{
		perror("Unterminated double quote");
		exit(EXIT_FAILURE);
	}
	return (pos);
}

int lex_var(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (ft_isalnum(input[pos]) || input[pos] == '_')
		pos++;
	len = pos - start;
	new_tkn = create_tkn(TKN_VAR, &input[start], len, start);
	append_tkn(&tokens, new_tkn);
	return (pos);
}

void	*malloc_perex(size_t bytes, char *msg)
{
	void	*res;

	res = malloc(bytes); 
	if (res == NULL)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
	return (res);
}

// Lexer function
t_token *lexer(const char *input) {
    t_token *tokens = NULL;
    t_token *new_tkn = NULL;
    int pos = 0;
    t_token *eof_tkn;

    while (input[pos]) {
        if (ft_isspace(input[pos])) {
            pos++;
        } else if (input[pos] == '|') {
            pos = lex_or_pipe(input, pos, tokens, new_tkn);
        } else if (input[pos] == '&') {
            pos = lex_and_bg(input, pos, tokens, new_tkn);
        } else if (input[pos] == '<') {
            pos = lex_hd_rin(input, pos, tokens, new_tkn);
        } else if (input[pos] == '>') {
            pos = lex_app_rout(input, pos, tokens, new_tkn);
        } else if (input[pos] == ';') {
            pos = lex_single_sym(input, pos, tokens, new_tkn);
        } else if (input[pos] == '(') {
            pos = lex_single_sym(input, pos, tokens, new_tkn);
        } else if (input[pos] == ')') {
            pos = lex_single_sym(input, pos, tokens, new_tkn);
        } else if (input[pos] == '\'') {
            pos = lex_quo_sin(input, pos, tokens, new_tkn);
        } else if (input[pos] == '"') {
            pos = lex_quo_dou(input, pos, tokens, new_tkn);
        } else if (input[pos] == '$') {
            pos = lex_var(input, pos, tokens, new_tkn);
        } else {
            pos = lex_word(input, pos, &tokens, new_tkn);  // Call lex_word function here
        }
    }

    // Add EOF token
    eof_tkn = create_tkn(TKN_EOF, "", 0, pos);
    append_tkn(&tokens, eof_tkn);

    return tokens;
}

// Function to create a token
t_token *create_tkn(t_tkntype type, const char *start, int len, int pos) {
    t_token *token = malloc_perex(sizeof(t_token), "Malloc error on create_tkn");
    token->type = type;
    token->value = malloc_perex(len + 1, "Malloc error on create_tkn val");
    ft_strlcpy(token->value, start, len + 1);
    token->position = pos;
    token->next = NULL;
    return token;
}

// Function to append a token to the linked list
void append_tkn(t_token **head, t_token *new_token) {
    t_token *temp;

    if (!*head) {
        *head = new_token;
    } else {
        temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
}

// New function to handle TKN_WORD
int lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn) {
    int start = pos;

    // Find the end of the word
    while (input[pos] && !ft_isspace(input[pos]) && !ft_strchr("|&;<>$()'\"", input[pos]))
        pos++;

    // Calculate the length and create a token
    int len = pos - start;
    new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
    append_tkn(tokens, new_tkn);

    return pos;  // Return the updated position
}

// Function to print tokens
void print_tkn(t_token *tokens) {
    t_token *current = tokens;
    while (current) {
        printf("Type: %d, Value: '%s', Position: %d\n",
               current->type, current->value, current->position);
        current = current->next;
    }
}

// Function to free tokens
void free_tkn(t_token *tokens) {
    t_token *current = tokens;
    while (current) {
        t_token *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

// Main function
int main() {
    const char *input = "  cat file.txt | grep \"search term\" > output.txt";
    t_token *tokens = lexer(input);
    print_tkn(tokens);
    free_tkn(tokens);
    return 0;
}
