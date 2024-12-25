#include "../tests.h"

// Test lex_or_pipe function
START_TEST(test_lex_or_pipe)
{
	const char	*input = "|| |";
	t_token		*tokens;

	tokens = NULL;
	tokens = lexer(input);
	ck_assert_int_eq(tokens->type, TKN_OR);
	ck_assert_str_eq(tokens->value, "||");
	tokens = tokens->next;
	ck_assert_int_eq(tokens->type, TKN_PIPE);
	ck_assert_str_eq(tokens->value, "|");
	free_tkn(tokens);
}
END_TEST

// Test lex_and_bg function
START_TEST(test_lex_and_bg)
{
	const char	*input = "&& &";
	t_token		*tokens;

	tokens = NULL;
	tokens = lexer(input);
	ck_assert_int_eq(tokens->type, TKN_AND);
	ck_assert_str_eq(tokens->value, "&&");
	tokens = tokens->next;
	ck_assert_int_eq(tokens->type, TKN_BG);
	ck_assert_str_eq(tokens->value, "&");
	free_tkn(tokens);
}
END_TEST

// Test lex_semi_col function
START_TEST(test_lex_semi_col)
{
	const char	*input = ";";
	t_token		*tokens;

	tokens = NULL;

	tokens = lexer(input);
	ck_assert_int_eq(tokens->type, TKN_SEMCOL);
	ck_assert_str_eq(tokens->value, ";");
	free_tkn(tokens);
}
END_TEST

// Function to create Operator Lexer Test Suite
Suite	*lexer_operator_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Lexer Operator");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_lex_or_pipe);
	tcase_add_test(tc_core, test_lex_and_bg);
	tcase_add_test(tc_core, test_lex_semi_col);
	suite_add_tcase(s, tc_core);
	return (s);
}
