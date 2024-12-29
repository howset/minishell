#include "../tests.h"

START_TEST(test_parse_logical_and)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("ls && echo test");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_AND);
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->args_count, 1);
	ck_assert_str_eq(ast->left->args[0], "ls");
	ck_assert_ptr_nonnull(ast->right);
	ck_assert_int_eq(ast->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->right->args_count, 2);
	ck_assert_str_eq(ast->right->args[0], "echo");
	ck_assert_str_eq(ast->right->args[1], "test");
	free_ast(ast);
	free_tkn(tokens);
}

START_TEST(test_parse_logical_or)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("ls || echo test");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_OR);
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->args_count, 1);
	ck_assert_str_eq(ast->left->args[0], "ls");
	ck_assert_ptr_nonnull(ast->right);
	ck_assert_int_eq(ast->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->right->args_count, 2);
	ck_assert_str_eq(ast->right->args[0], "echo");
	ck_assert_str_eq(ast->right->args[1], "test");
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

START_TEST(test_parse_logical_multiple)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("ls && echo test || echo test2");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_OR);
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_AND);
	ck_assert_ptr_nonnull(ast->left->left);
	ck_assert_int_eq(ast->left->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->left->args_count, 1);
	ck_assert_str_eq(ast->left->left->args[0], "ls");
	ck_assert_ptr_nonnull(ast->left->right);
	ck_assert_int_eq(ast->left->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->right->args_count, 2);
	ck_assert_str_eq(ast->left->right->args[0], "echo");
	ck_assert_str_eq(ast->left->right->args[1], "test");
	ck_assert_ptr_nonnull(ast->right);
	ck_assert_int_eq(ast->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->right->args_count, 2);
	ck_assert_str_eq(ast->right->args[0], "echo");
	ck_assert_str_eq(ast->right->args[1], "test2");
	free_ast(ast);
	free_tkn(tokens);
}

Suite	*parser_logical_suite(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("Parser Logical");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_parse_logical_and);
	tcase_add_test(tc_core, test_parse_logical_or);
	tcase_add_test(tc_core, test_parse_logical_multiple);
	suite_add_tcase(s, tc_core);
	return (s);
}
