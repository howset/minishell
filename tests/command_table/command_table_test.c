#include "../tests.h"

// Test simple command
START_TEST(test_simple_command)
{
	char		*cmd;
	t_token		*tokens;
	t_ast		*ast;
	t_cmdtable	*table;

	cmd = "ls -l";
	tokens = lexer(cmd);
	ast = parse(tokens);
	table = ast_to_command_table(ast);
	ck_assert_ptr_nonnull(table);
	ck_assert_int_eq(table->cmd_count, 1);
	ck_assert_int_eq(table->pipe_count, 0);
	ck_assert_ptr_nonnull(table->commands);
	ck_assert_str_eq(table->commands->args[0], "ls");
	ck_assert_str_eq(table->commands->args[1], "-l");
	ck_assert_ptr_null(table->commands->args[2]);
}
END_TEST

// Test pipe command
START_TEST(test_pipe_command)
{
	char		*cmd;
	t_token		*tokens;
	t_ast		*ast;
	t_cmdtable	*table;

	cmd = "ls -l | grep test";
	tokens = lexer(cmd);
	ast = parse(tokens);
	table = ast_to_command_table(ast);
	ck_assert_ptr_nonnull(table);
	ck_assert_int_eq(table->cmd_count, 2);
	ck_assert_int_eq(table->pipe_count, 1);
	// Check first command
	ck_assert_ptr_nonnull(table->commands);
	ck_assert_str_eq(table->commands->args[0], "ls");
	ck_assert_str_eq(table->commands->args[1], "-l");
	ck_assert_int_ne(table->commands->pipe_write, -1);
	// Check second command
	ck_assert_ptr_nonnull(table->commands->next);
	ck_assert_str_eq(table->commands->next->args[0], "grep");
	ck_assert_str_eq(table->commands->next->args[1], "test");
	ck_assert_int_ne(table->commands->next->pipe_read, -1);
}
END_TEST

// Test redirection
START_TEST(test_redirection)
{
	char		*cmd;
	t_token		*tokens;
	t_ast		*ast;
	t_cmdtable	*table;

	cmd = "cat file.txt > output.txt";
	tokens = lexer(cmd);
	ast = parse(tokens);
	table = ast_to_command_table(ast);
	ck_assert_ptr_nonnull(table);
	ck_assert_int_eq(table->cmd_count, 1);
	ck_assert_ptr_nonnull(table->commands);
	ck_assert_ptr_nonnull(table->commands->redirections);
	ck_assert_int_eq(table->commands->redirections->type, TKN_RDIR_OUT);
	ck_assert_str_eq(table->commands->redirections->file, "output.txt");
}
END_TEST

// Test sequence
START_TEST(test_sequence)
{
	char		*cmd;
	t_token		*tokens;
	t_ast		*ast;
	t_cmdtable	*table;

	cmd = "echo hello; echo world";
	tokens = lexer(cmd);
	ast = parse(tokens);
	table = ast_to_command_table(ast);
	ck_assert_ptr_nonnull(table);
	ck_assert_int_eq(table->cmd_count, 2);
	ck_assert_int_eq(table->pipe_count, 0);
	ck_assert_ptr_nonnull(table->commands);
	ck_assert_str_eq(table->commands->args[0], "echo");
	ck_assert_str_eq(table->commands->args[1], "hello");
	ck_assert_ptr_nonnull(table->commands->next);
	ck_assert_str_eq(table->commands->next->args[0], "echo");
	ck_assert_str_eq(table->commands->next->args[1], "world");
}
END_TEST

// Test multiple redirections
START_TEST(test_multiple_redirections)
{
	char			*cmd;
	t_token			*tokens;
	t_ast			*ast;
	t_cmdtable		*table;
	t_redirection	*redir;

	cmd = "cat < input.txt > output.txt";
	tokens = lexer(cmd);
	ast = parse(tokens);
	table = ast_to_command_table(ast);
	ck_assert_ptr_nonnull(table);
	ck_assert_int_eq(table->cmd_count, 1);
	// Check command
	ck_assert_ptr_nonnull(table->commands);
	ck_assert_str_eq(table->commands->args[0], "cat");
	// Check redirections
	redir = table->commands->redirections;
	ck_assert_ptr_nonnull(redir);
	// First redirection should be input
	ck_assert_int_eq(redir->type, TKN_RDIR_IN);
	ck_assert_str_eq(redir->file, "input.txt");
	// Second redirection should be output
	ck_assert_ptr_nonnull(redir->next);
	ck_assert_int_eq(redir->next->type, TKN_RDIR_OUT);
	ck_assert_str_eq(redir->next->file, "output.txt");
}
END_TEST

// Test complex pipeline
START_TEST(test_complex_pipeline)
{
	char			*command;
	t_token			*tokens;
	t_ast			*ast;
	t_cmdtable		*table;
	t_command		*cmd;

	command = "cat file.txt | grep pattern | sort | uniq";
	tokens = lexer(command);
	ast = parse(tokens);
	table = ast_to_command_table(ast);
	ck_assert_ptr_nonnull(table);
	ck_assert_int_eq(table->cmd_count, 4);
	ck_assert_int_eq(table->pipe_count, 3);
	// Check all commands in sequence
	cmd = table->commands;
	ck_assert_str_eq(cmd->args[0], "cat");
	ck_assert_str_eq(cmd->args[1], "file.txt");
	ck_assert_int_ne(cmd->pipe_write, -1);
	cmd = cmd->next;
	ck_assert_str_eq(cmd->args[0], "grep");
	ck_assert_str_eq(cmd->args[1], "pattern");
	ck_assert_int_ne(cmd->pipe_read, -1);
	ck_assert_int_ne(cmd->pipe_write, -1);
	cmd = cmd->next;
	ck_assert_str_eq(cmd->args[0], "sort");
	ck_assert_int_ne(cmd->pipe_read, -1);
	ck_assert_int_ne(cmd->pipe_write, -1);
	cmd = cmd->next;
	ck_assert_str_eq(cmd->args[0], "uniq");
	ck_assert_int_ne(cmd->pipe_read, -1);
}
END_TEST

// // Test subshell
// START_TEST(test_subshell)
// {
// 	char			*cmd;
// 	t_token			*tokens;
// 	t_ast			*ast;
// 	t_cmdtable		*table;

// 	cmd = "(echo test)";
// 	tokens = lexer(cmd);
// 	ast = parse(tokens);
// 	print_ast(ast, 0);
// 	table = ast_to_command_table(ast);
// 	ck_assert_ptr_nonnull(table);
// 	ck_assert_int_eq(table->cmd_count, 1);
// 	ck_assert_ptr_nonnull(table->commands);
// 	ck_assert_int_eq(table->commands->type, CMD_SUBSHELL);
// 	ck_assert_str_eq(table->commands->args[0], "echo");
// 	ck_assert_str_eq(table->commands->args[1], "test");
// }
END_TEST

Suite	*command_table_suite(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("Command Table");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_simple_command);
	tcase_add_test(tc_core, test_pipe_command);
	tcase_add_test(tc_core, test_redirection);
	tcase_add_test(tc_core, test_sequence);
	tcase_add_test(tc_core, test_multiple_redirections);
	tcase_add_test(tc_core, test_complex_pipeline);
	// tcase_add_test(tc_core, test_subshell);
	suite_add_tcase(s, tc_core);
	return (s);
}
