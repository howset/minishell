#include "lexer.h"

int	lex_or_pipe(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '|')
	{
		new_tkn = create_tkn(TKN_OR, &input[pos], 2, pos);
		append_tkn(tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_PIPE, &input[pos], 1, pos);
		append_tkn(tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int	lex_and_bg(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '&')
	{
		new_tkn = create_tkn(TKN_AND, &input[pos], 2, pos);
		append_tkn(tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_BG, &input[pos], 1, pos);
		append_tkn(tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int	lex_semi_col(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	new_tkn = create_tkn(TKN_SEMCOL, &input[pos], 1, pos);
	append_tkn(tokens, new_tkn);
	pos++;
	return (pos);
}