#include "lexer.h"

int	lex_paren_op(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	new_tkn = create_tkn(TKN_PAREN_OP, &input[pos], 1, pos);
	append_tkn(tokens, new_tkn);
	pos++;
	return (pos);
}

int	lex_paren_cl(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	new_tkn = create_tkn(TKN_PAREN_CL, &input[pos], 1, pos);
	append_tkn(tokens, new_tkn);
	pos++;
	return (pos);
}