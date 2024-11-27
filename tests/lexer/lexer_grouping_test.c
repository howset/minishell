#include "../../src/lexer/lexer.h"
#include "../../src/minishell.h"
#include <check.h>

// Advanced Lexer Test Case
START_TEST(test_lex_paren_op)
{
	const char	*input = "()";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_PAREN_OP);
	ck_assert_str_eq(tokens->value, "(");
	tokens = tokens->next;
	ck_assert_int_eq(tokens->type, TKN_PAREN_CL);
	ck_assert_str_eq(tokens->value, ")");
	free_tkn(tokens);
}
END_TEST

START_TEST(test_lex_paren_cl)
{
	const char	*input = ")(";
	t_token		*tokens;

	tokens = lexer(input);
	ck_assert_ptr_nonnull(tokens);
	ck_assert_int_eq(tokens->type, TKN_PAREN_CL);
	ck_assert_str_eq(tokens->value, ")");
	tokens = tokens->next;
	ck_assert_int_eq(tokens->type, TKN_PAREN_OP);
	ck_assert_str_eq(tokens->value, "(");
	free_tkn(tokens);
}

// Function to create Lexer Grouping Test Suite
Suite	*lexer_grouping_suite(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("Lexer Grouping");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_lex_paren_op);
	tcase_add_test(tc_core, test_lex_paren_cl);
	suite_add_tcase(s, tc_core);
	return (s);
}
