#include "../../src/lexer/lexer.h"
#include "../../src/minishell.h"
#include <check.h>

// Test lex_var function
START_TEST(test_lex_var)
{
	const char	*input = "$variable";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_VAR);
	ck_assert_str_eq(tokens->value, "$variable");
	free_tkn(tokens);
}
END_TEST

// Test lex_word function
START_TEST(test_lex_word)
{
	const char	*input = "word";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_WORD);
	ck_assert_str_eq(tokens->value, "word");
	free_tkn(tokens);
}
END_TEST

// Function to create Lexer Word Test Suite
Suite	*lexer_word_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Lexer Word");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_lex_var);
	tcase_add_test(tc_core, test_lex_word);
	suite_add_tcase(s, tc_core);
	return (s);
}