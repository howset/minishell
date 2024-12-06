#include <check.h>
#include "../../src/command_table/command_table.h"

// Helper function to create a simple command AST node
static t_ast *create_command_ast(char **args)
{
    t_ast *node;
    int count;

    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;

    node->type = NODE_COMMAND;
    node->left = NULL;
    node->right = NULL;

    // Count and duplicate arguments
    count = 0;
    while (args[count])
        count++;

    node->args = malloc(sizeof(char *) * (count + 1));
    if (!node->args)
    {
        free(node);
        return NULL;
    }

    for (int i = 0; i < count; i++)
    {
        node->args[i] = ft_strdup(args[i]);
        if (!node->args[i])
        {
            while (--i >= 0)
                free(node->args[i]);
            free(node->args);
            free(node);
            return NULL;
        }
    }
    node->args[count] = NULL;
    node->args_count = count;
    node->redirection_type = TKN_INVALID;
    node->filename = NULL;

    return node;
}

// Helper function to create a redirection AST node
static t_ast *create_redirection_ast(t_ast *child, t_tkntype type, char *filename)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;

    node->type = NODE_REDIRECTION;
    node->left = child;
    node->right = NULL;
    node->args = NULL;
    node->args_count = 0;
    node->redirection_type = type;
    node->filename = ft_strdup(filename);
    if (!node->filename)
    {
        free(node);
        return NULL;
    }

    return node;
}

// Helper function to create a pipe AST node
static t_ast *create_pipe_ast(t_ast *left, t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;

    node->type = NODE_PIPE;
    node->left = left;
    node->right = right;
    node->args = NULL;
    node->args_count = 0;
    node->redirection_type = TKN_INVALID;
    node->filename = NULL;

    return node;
}

// Helper function to create a sequence AST node
static t_ast *create_sequence_ast(t_ast *left, t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;

    node->type = NODE_SEQUENCE;
    node->left = left;
    node->right = right;
    node->args = NULL;
    node->args_count = 0;
    node->redirection_type = TKN_INVALID;
    node->filename = NULL;

    return node;
}

// Helper function to create a subshell AST node
static t_ast *create_subshell_ast(t_ast *child)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;

    node->type = NODE_SUBSHELL;
    node->left = child;
    node->right = NULL;
    node->args = NULL;
    node->args_count = 0;
    node->redirection_type = TKN_INVALID;
    node->filename = NULL;

    return node;
}

// Helper function to free AST
static void free_ast_node(t_ast *node)
{
    if (!node)
        return;

    free_ast_node(node->left);
    free_ast_node(node->right);

    if (node->args)
    {
        for (int i = 0; i < node->args_count; i++)
            free(node->args[i]);
        free(node->args);
    }
    if (node->filename)
        free(node->filename);
    free(node);
}

// Test simple command
START_TEST(test_simple_command)
{
    char *args[] = {"ls", "-l", NULL};
    t_ast *ast = create_command_ast(args);
    t_cmdtable *table = ast_to_command_table(ast);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->cmd_count, 1);
    ck_assert_int_eq(table->pipe_count, 0);
    ck_assert_ptr_nonnull(table->commands);
    ck_assert_str_eq(table->commands->args[0], "ls");
    ck_assert_str_eq(table->commands->args[1], "-l");
    ck_assert_ptr_null(table->commands->args[2]);

    free_command_table(table);
    free_ast_node(ast);
}
END_TEST

// Test pipe command
START_TEST(test_pipe_command)
{
    char *left_args[] = {"ls", "-l", NULL};
    char *right_args[] = {"grep", "test", NULL};

    t_ast *left = create_command_ast(left_args);
    t_ast *right = create_command_ast(right_args);
    t_ast *pipe = create_pipe_ast(left, right);

    t_cmdtable *table = ast_to_command_table(pipe);

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

    free_command_table(table);
    free_ast_node(pipe);
}
END_TEST

// Test redirection
START_TEST(test_redirection)
{
    char *args[] = {"cat", "file.txt", NULL};
    t_ast *cmd = create_command_ast(args);
    t_ast *redir = create_redirection_ast(cmd, TKN_RDIR_OUT, "output.txt");

    t_cmdtable *table = ast_to_command_table(redir);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->cmd_count, 1);
    ck_assert_ptr_nonnull(table->commands);
    ck_assert_ptr_nonnull(table->commands->redirections);
    ck_assert_int_eq(table->commands->redirections->type, TKN_RDIR_OUT);
    ck_assert_str_eq(table->commands->redirections->file, "output.txt");

    free_command_table(table);
    free_ast_node(redir);
}
END_TEST

// Test sequence
START_TEST(test_sequence)
{
    char *first_args[] = {"echo", "hello", NULL};
    char *second_args[] = {"echo", "world", NULL};

    t_ast *first = create_command_ast(first_args);
    t_ast *second = create_command_ast(second_args);
    t_ast *seq = create_sequence_ast(first, second);

    t_cmdtable *table = ast_to_command_table(seq);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->cmd_count, 2);
    ck_assert_int_eq(table->pipe_count, 0);

    ck_assert_ptr_nonnull(table->commands);
    ck_assert_str_eq(table->commands->args[0], "echo");
    ck_assert_str_eq(table->commands->args[1], "hello");

    ck_assert_ptr_nonnull(table->commands->next);
    ck_assert_str_eq(table->commands->next->args[0], "echo");
    ck_assert_str_eq(table->commands->next->args[1], "world");

    free_command_table(table);
    free_ast_node(seq);
}
END_TEST

// Test multiple redirections
START_TEST(test_multiple_redirections)
{
    char *args[] = {"cat", NULL};
    t_ast *cmd = create_command_ast(args);
    t_ast *in_redir = create_redirection_ast(cmd, TKN_RDIR_IN, "input.txt");
    t_ast *out_redir = create_redirection_ast(in_redir, TKN_RDIR_OUT, "output.txt");

    t_cmdtable *table = ast_to_command_table(out_redir);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->cmd_count, 1);

    // Check command
    ck_assert_ptr_nonnull(table->commands);
    ck_assert_str_eq(table->commands->args[0], "cat");

    // Check redirections
    t_redirection *redir = table->commands->redirections;
    ck_assert_ptr_nonnull(redir);

    // First redirection should be input
    ck_assert_int_eq(redir->type, TKN_RDIR_IN);
    ck_assert_str_eq(redir->file, "input.txt");

    // Second redirection should be output
    ck_assert_ptr_nonnull(redir->next);
    ck_assert_int_eq(redir->next->type, TKN_RDIR_OUT);
    ck_assert_str_eq(redir->next->file, "output.txt");

    free_command_table(table);
    free_ast_node(out_redir);
}
END_TEST

// Test complex pipeline
START_TEST(test_complex_pipeline)
{
    // Create a complex pipeline: cat file.txt | grep pattern | sort | uniq
    char *cmd1_args[] = {"cat", "file.txt", NULL};
    char *cmd2_args[] = {"grep", "pattern", NULL};
    char *cmd3_args[] = {"sort", NULL};
    char *cmd4_args[] = {"uniq", NULL};

    t_ast *cmd1 = create_command_ast(cmd1_args);
    t_ast *cmd2 = create_command_ast(cmd2_args);
    t_ast *cmd3 = create_command_ast(cmd3_args);
    t_ast *cmd4 = create_command_ast(cmd4_args);

    t_ast *pipe1 = create_pipe_ast(cmd1, cmd2);
    t_ast *pipe2 = create_pipe_ast(pipe1, cmd3);
    t_ast *pipe3 = create_pipe_ast(pipe2, cmd4);

    t_cmdtable *table = ast_to_command_table(pipe3);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->cmd_count, 4);
    ck_assert_int_eq(table->pipe_count, 3);

    // Check all commands in sequence
    t_command *cmd = table->commands;
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

    free_command_table(table);
    free_ast_node(pipe3);
}
END_TEST

// Test subshell
START_TEST(test_subshell)
{
    char *args[] = {"echo", "test", NULL};
    t_ast *cmd = create_command_ast(args);
    t_ast *subshell = create_subshell_ast(cmd);

    t_cmdtable *table = ast_to_command_table(subshell);

    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->cmd_count, 1);
    ck_assert_ptr_nonnull(table->commands);
    ck_assert_int_eq(table->commands->type, CMD_SUBSHELL);
    ck_assert_str_eq(table->commands->args[0], "echo");
    ck_assert_str_eq(table->commands->args[1], "test");

    free_command_table(table);
    free_ast_node(subshell);
}
END_TEST

Suite *command_table_suite(void)
{
    Suite *s = suite_create("Command Table");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_simple_command);
    tcase_add_test(tc_core, test_pipe_command);
    tcase_add_test(tc_core, test_redirection);
    tcase_add_test(tc_core, test_sequence);
    tcase_add_test(tc_core, test_multiple_redirections);
    tcase_add_test(tc_core, test_complex_pipeline);
    tcase_add_test(tc_core, test_subshell);

    suite_add_tcase(s, tc_core);
    return s;
}
