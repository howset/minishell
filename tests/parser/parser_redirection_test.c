#include "../tests.h"

START_TEST(test_parse_redirection)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("cat < input.txt > output.txt");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_REDIRECTION);
	ck_assert_str_eq(ast->filename, "output.txt");
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_REDIRECTION);
	ck_assert_str_eq(ast->left->filename, "input.txt");
	ck_assert_ptr_nonnull(ast->left->left);
	ck_assert_int_eq(ast->left->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->left->args_count, 1);
	ck_assert_str_eq(ast->left->left->args[0], "cat");
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

START_TEST(test_parse_input_redirection)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("cat < input.txt");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_REDIRECTION);
	ck_assert_str_eq(ast->filename, "input.txt");
	ck_assert_int_eq(ast->redirection_type, TKN_RDIR_IN);
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->args_count, 1);
	ck_assert_str_eq(ast->left->args[0], "cat");
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

START_TEST(test_parse_output_redirection)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("echo hello > output.txt");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_REDIRECTION);
	ck_assert_str_eq(ast->filename, "output.txt");
	ck_assert_int_eq(ast->redirection_type, TKN_RDIR_OUT);
	ck_assert_ptr_nonnull(ast->left);
	ck_assert_int_eq(ast->left->type, NODE_COMMAND);
	ck_assert_int_eq(ast->left->args_count, 2);
	ck_assert_str_eq(ast->left->args[0], "echo");
	ck_assert_str_eq(ast->left->args[1], "hello");
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

START_TEST(test_parse_append_redirection)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("echo hello >> output.txt");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, TKN_RDIR_IN);
	ck_assert_str_eq(ast->filename, "output.txt");
	ck_assert_int_eq(ast->redirection_type, TKN_APPEND);
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

START_TEST(test_parse_heredoc)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("cat << EOF");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_REDIRECTION);
	ck_assert_int_eq(ast->redirection_type, TKN_HEREDOC);
	free_ast(ast);
	free_tkn(tokens);
}
END_TEST

Suite	*parser_redirection_suite(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("Parser Redirection");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_parse_redirection);
	tcase_add_test(tc_core, test_parse_input_redirection);
	tcase_add_test(tc_core, test_parse_output_redirection);
	tcase_add_test(tc_core, test_parse_append_redirection);
	tcase_add_test(tc_core, test_parse_heredoc);
	suite_add_tcase(s, tc_core);
	return (s);
}
