#include "../tests.h"

// Helper function to create a simple AST node for testing
static t_ast *create_test_command_node(char **args)
{
    t_ast *node = create_ast_node(NODE_COMMAND);
    if (!node)
        return NULL;

    int i = 0;
    while (args[i])
    {
        node->args_count++;
        node->args = realloc(node->args, sizeof(char *) * (node->args_count + 1));
        node->args[node->args_count - 1] = ft_strdup(args[i]);
        node->args[node->args_count] = NULL;
        i++;
    }
    return node;
}

// Test simple command conversion
START_TEST(test_simple_command)
{
    char *args[] = {"ls", "-l", NULL};
    t_ast *ast = create_test_command_node(args);
    t_commtab *table = ast_to_commtab(ast);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->count, 1);
    ck_assert_str_eq(table->commands[0].args[0], "ls");
    ck_assert_str_eq(table->commands[0].args[1], "-l");
    ck_assert_ptr_null(table->commands[0].args[2]);
    ck_assert_ptr_null(table->commands[0].in_redir);
    ck_assert_ptr_null(table->commands[0].out_redir);
    ck_assert_int_eq(table->commands[0].is_bg, 0);

    free_ast(ast);
    // TODO: Add free_commtab function
}
END_TEST

// Test command with input redirection
START_TEST(test_input_redirection)
{
    t_ast *cmd_node = create_test_command_node((char *[]){"cat", NULL});
    t_ast *redir_node = create_ast_node(NODE_REDIRECTION);
    redir_node->redirection_type = TKN_RDIR_IN;
    redir_node->filename = ft_strdup("input.txt");
    redir_node->left = cmd_node;

    t_commtab *table = ast_to_commtab(redir_node);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->count, 1);
    ck_assert_str_eq(table->commands[0].args[0], "cat");
    ck_assert_str_eq(table->commands[0].in_redir, "input.txt");
    ck_assert_ptr_null(table->commands[0].out_redir);

    free_ast(redir_node);
    // TODO: Add free_commtab function
}
END_TEST

// Test command with output redirection
START_TEST(test_output_redirection)
{
    t_ast *cmd_node = create_test_command_node((char *[]){"echo", "hello", NULL});
    t_ast *redir_node = create_ast_node(NODE_REDIRECTION);
    redir_node->redirection_type = TKN_RDIR_OUT;
    redir_node->filename = ft_strdup("output.txt");
    redir_node->left = cmd_node;

    t_commtab *table = ast_to_commtab(redir_node);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->count, 1);
    ck_assert_str_eq(table->commands[0].args[0], "echo");
    ck_assert_str_eq(table->commands[0].args[1], "hello");
    ck_assert_ptr_null(table->commands[0].in_redir);
    ck_assert_str_eq(table->commands[0].out_redir, "output.txt");

    free_ast(redir_node);
    // TODO: Add free_commtab function
}
END_TEST

// Test pipe command
START_TEST(test_pipe_command)
{
    t_ast *left_cmd = create_test_command_node((char *[]){"ls", "-l", NULL});
    t_ast *right_cmd = create_test_command_node((char *[]){"grep", "test", NULL});
    t_ast *pipe_node = create_ast_node(NODE_PIPE);
    pipe_node->left = left_cmd;
    pipe_node->right = right_cmd;

    t_commtab *table = ast_to_commtab(pipe_node);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->count, 2);
    ck_assert_str_eq(table->commands[0].args[0], "ls");
    ck_assert_str_eq(table->commands[0].args[1], "-l");
    ck_assert_str_eq(table->commands[1].args[0], "grep");
    ck_assert_str_eq(table->commands[1].args[1], "test");

    free_ast(pipe_node);
    // TODO: Add free_commtab function
}
END_TEST

// Test background command
START_TEST(test_background_command)
{
    t_ast *cmd_node = create_test_command_node((char *[]){"sleep", "10", "&", NULL});
    t_commtab *table = ast_to_commtab(cmd_node);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->count, 1);
    ck_assert_str_eq(table->commands[0].args[0], "sleep");
    ck_assert_str_eq(table->commands[0].args[1], "10");
    ck_assert_str_eq(table->commands[0].args[2], "&");
    ck_assert_int_eq(table->commands[0].is_bg, 1);

    free_ast(cmd_node);
    // TODO: Add free_commtab function
}
END_TEST

// Test sequence of commands
START_TEST(test_sequence_command)
{
    t_ast *left_cmd = create_test_command_node((char *[]){"echo", "first", NULL});
    t_ast *right_cmd = create_test_command_node((char *[]){"echo", "second", NULL});
    t_ast *seq_node = create_ast_node(NODE_SEQUENCE);
    seq_node->left = left_cmd;
    seq_node->right = right_cmd;

    t_commtab *table = ast_to_commtab(seq_node);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->count, 2);
    ck_assert_str_eq(table->commands[0].args[0], "echo");
    ck_assert_str_eq(table->commands[0].args[1], "first");
    ck_assert_str_eq(table->commands[1].args[0], "echo");
    ck_assert_str_eq(table->commands[1].args[1], "second");

    free_ast(seq_node);
    // TODO: Add free_commtab function
}
END_TEST

Suite *parser_command_table_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Parser Command Table");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_simple_command);
    tcase_add_test(tc_core, test_input_redirection);
    tcase_add_test(tc_core, test_output_redirection);
    tcase_add_test(tc_core, test_pipe_command);
    tcase_add_test(tc_core, test_background_command);
    tcase_add_test(tc_core, test_sequence_command);

    suite_add_tcase(s, tc_core);
    return s;
}
