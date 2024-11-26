#ifndef LEXER_H
# define LEXER_H

#include "../includes.h"

typedef enum e_tkntype
{
	TKN_OR, //0
	TKN_PIPE, //1
	TKN_BG, //2
	TKN_AND, //3
	TKN_RDIR_IN, //4
	TKN_HEREDOC, //5
	TKN_RDIR_OUT, //6
	TKN_APPEND, //7
	TKN_SEMCOL, //8
	TKN_PAREN_OP, //9
	TKN_PAREN_CL, //10
	TKN_QUO_SIN, //11
	TKN_QUO_DOU, //12
	TKN_VAR, //13
	TKN_WORD, //14
	TKN_EOF, //15
}	t_tkntype;

typedef struct s_token{
	t_tkntype		type;
	char			*value;
	int				position;
	struct s_token	*next;
	//struct s_token	*prev; //doubly linked
}	t_token;

//lexer.c
t_token	*lexer(const char *input);

//token.c
t_token	*create_tkn(t_tkntype type, const char *start, int len, int pos);
void	append_tkn(t_token **head, t_token *new_token);
void	print_tkn(t_token *tokens);
void	free_tkn(t_token *tokens);

//operator.c
int lex_or_pipe(const char *input, int pos, t_token **tokens, t_token *new_tkn);
int lex_and_bg(const char *input, int pos, t_token **tokens, t_token *new_tkn);
int	lex_semi_col(const char *input, int pos, t_token **tokens, t_token *new_tkn);

//redirection.c
int lex_hd_rin(const char *input, int pos, t_token **tokens, t_token *new_tkn);
int lex_app_rout(const char *input, int pos, t_token **tokens, t_token *new_tkn);

//grouping.c
int lex_paren_op(const char *input, int pos, t_token **tokens, t_token *new_tkn);
int lex_paren_cl(const char *input, int pos, t_token **tokens, t_token *new_tkn);

//quote.c
int lex_quo_sin(const char *input, int pos, t_token **tokens, t_token *new_tkn);
int lex_quo_dou(const char *input, int pos, t_token **tokens, t_token *new_tkn);

//word.c
int lex_var(const char *input, int pos, t_token **tokens, t_token *new_tkn);
//int lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn);
int lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn);
//int lex_word(const char *input, int pos, t_token **tokens);


#endif
