#include "../tests.h"

START_TEST(test_parse_echo_command)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("echo hello world");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_COMMAND);
	ck_assert_int_eq(ast->args_count, 3);
	ck_assert_str_eq(ast->args[0], "echo");
	ck_assert_str_eq(ast->args[1], "hello");
	ck_assert_str_eq(ast->args[2], "world");
	free_ast(ast);
	free_tkn(tokens);
}

END_TEST

START_TEST(test_variables_replacement)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	all_data->env_head = create_env_var("PWD", "hello");
	tokens = lexer("echo $PWD");
	ast = parse(tokens, all_data);
	print_tkn(tokens);
	print_ast(ast, 0);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_COMMAND);
	ck_assert_int_eq(ast->args_count, 2);
	ck_assert_str_eq(ast->args[0], "echo");
	ck_assert_str_eq(ast->args[1], "hello");
	free_ast(ast);
	free_tkn(tokens);
}

END_TEST

START_TEST(test_parse_simple_command)
{
	t_token		*tokens;
	t_ast		*ast;
	t_alldata	*all_data;

	all_data = initialize_test_alldata();
	tokens = lexer("ls -la");
	ast = parse(tokens, all_data);
	ck_assert_ptr_nonnull(ast);
	ck_assert_int_eq(ast->type, NODE_COMMAND);
	ck_assert_int_eq(ast->args_count, 2);
	ck_assert_str_eq(ast->args[0], "ls");
	ck_assert_str_eq(ast->args[1], "-la");
	free_ast(ast);
	free_tkn(tokens);
}

END_TEST

Suite	*parser_simple_command_suite(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("Parser Simple Command");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_parse_simple_command);
	tcase_add_test(tc_core, test_parse_echo_command);
	tcase_add_test(tc_core, test_variables_replacement);
	suite_add_tcase(s, tc_core);
	return (s);
}
