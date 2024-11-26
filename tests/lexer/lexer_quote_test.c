#include "../../src/lexer/lexer.h"
#include "../../src/minishell.h"
#include <check.h>

// Single Quote Lexer Test Case
START_TEST(test_lex_quo_sin)
{
	const char	*input = "'single quoted string'";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_QUO_SIN);
	ck_assert_str_eq(tokens->value, "'single quoted string'");
	free_tkn(tokens);
}
END_TEST

// Unterminated Single Quote Lexer Test Case
START_TEST(test_lex_quo_sin_unterminated)
{
	const char	*input = "'unterminated single quote";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_null(tokens);
}
END_TEST

// Double Quote Lexer Test Case
START_TEST(test_lex_quo_dou)
{
	const char	*input = "\"double quoted string\"";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_QUO_DOU);
	ck_assert_str_eq(tokens->value, "\"double quoted string\"");
	free_tkn(tokens);
}
END_TEST

// Unterminated Double Quote Lexer Test Case
START_TEST(test_lex_quo_dou_unterminated)
{
	const char	*input = "\"unterminated double quote";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_null(tokens);
}
END_TEST

// Function to create Quote Lexer Test Suite
Suite	*lexer_quote_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Lexer Quote");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_lex_quo_sin);
	tcase_add_exit_test(tc_core, test_lex_quo_sin_unterminated, 1);
	tcase_add_test(tc_core, test_lex_quo_dou);
	tcase_add_exit_test(tc_core, test_lex_quo_dou_unterminated, 1);
	suite_add_tcase(s, tc_core);
	return (s);
}