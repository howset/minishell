#include "../tests.h"

START_TEST(test_parse_pipe)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("ls -l | grep test");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_PIPE);
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->args_count, 2);
	ck_assert_str_eq(ast->left->args[0], "ls");
	ck_assert_str_eq(ast->left->args[1], "-l");
	ck_assert_ptr_nonnull(ast->right);
	ck_assert_int_eq(ast->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->right->args_count, 2);
	ck_assert_str_eq(ast->right->args[0], "grep");
	ck_assert_str_eq(ast->right->args[1], "test");
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

START_TEST(test_parse_multiple_pipe)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("ls -l | grep test | wc -l");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_PIPE);
	// First Pipe
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_PIPE);
	ck_assert_int_eq(ast->left->args_count, 0);
	// First command (ls -l)
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->left->args_count, 2);
	ck_assert_str_eq(ast->left->left->args[0], "ls");
	ck_assert_str_eq(ast->left->left->args[1], "-l");
	// Second pipe and grep command
	ck_assert_ptr_nonnull(ast->left->right);
	ck_assert_int_eq(ast->left->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->right->args_count, 2);
	ck_assert_str_eq(ast->left->right->args[0], "grep");
	ck_assert_str_eq(ast->left->right->args[1], "test");
	// Last command (wc -l)
	ck_assert_ptr_nonnull(ast->right);
	ck_assert_int_eq(ast->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->right->args_count, 2);
	ck_assert_str_eq(ast->right->args[0], "wc");
	ck_assert_str_eq(ast->right->args[1], "-l");
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

START_TEST(test_multiple_parsre_with_redirection)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("ls -l | grep test | wc -l > output.txt");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_PIPE);
	// First Pipe
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_PIPE);
	ck_assert_int_eq(ast->left->args_count, 0);
	// First command (ls -l)
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->left->args_count, 2);
	ck_assert_str_eq(ast->left->left->args[0], "ls");
	ck_assert_str_eq(ast->left->left->args[1], "-l");
	// Second pipe and grep command
	ck_assert_ptr_nonnull(ast->left->right);
	ck_assert_int_eq(ast->left->right->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->right->args_count, 2);
	ck_assert_str_eq(ast->left->right->args[0], "grep");
	ck_assert_str_eq(ast->left->right->args[1], "test");
	// Last command (wc -l)
	ck_assert_ptr_nonnull(ast->right);
	ck_assert_int_eq(ast->right->type, NODE_REDIRECTION);
	ck_assert_int_eq(ast->right->redirection_type, TKN_RDIR_OUT);
	ck_assert_str_eq(ast->right->filename, "output.txt");
	ck_assert_str_eq(ast->right->left->args[0], "wc");
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

Suite	*parser_pipe_suite(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("Parser Pipe");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_parse_pipe);
	tcase_add_test(tc_core, test_parse_multiple_pipe);
	tcase_add_test(tc_core, test_multiple_parsre_with_redirection);
	suite_add_tcase(s, tc_core);
	return (s);
}
