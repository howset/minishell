#include "../tests.h"

// Test for Heredoc Redirection
START_TEST(test_lex_hd_rin)
{
	const char	*input = "<<";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_HEREDOC);
	ck_assert_str_eq(tokens->value, "<<");
	free_tkn(tokens);
}
END_TEST

// Test for Input Redirection
START_TEST(test_lex_rdir_in)
{
	const char	*input = "<";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_RDIR_IN);
	ck_assert_str_eq(tokens->value, "<");
	free_tkn(tokens);
}
END_TEST

// Test for Append Redirection
START_TEST(test_lex_app_rout)
{
	const char	*input = ">>";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_APPEND);
	ck_assert_str_eq(tokens->value, ">>");
	free_tkn(tokens);
}
END_TEST

// Test for Output Redirection
START_TEST(test_lex_rdir_out)
{
	const char	*input = ">";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_RDIR_OUT);
	ck_assert_str_eq(tokens->value, ">");
	free_tkn(tokens);
}
END_TEST

// Function to create Lexer Redirection Test Suite
Suite	*lexer_redirection_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Lexer Redirection");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_lex_hd_rin);
	tcase_add_test(tc_core, test_lex_rdir_in);
	tcase_add_test(tc_core, test_lex_app_rout);
	tcase_add_test(tc_core, test_lex_rdir_out);
	suite_add_tcase(s, tc_core);
	return (s);
}
