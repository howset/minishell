#include "../tests.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

START_TEST(test_rh_env_no_args)
{
	char	*args[] = {"env", NULL};
	char	*envp[] = {"PATH=/bin", NULL};
	t_env	*env_list;
	t_env	env_node = {"HOME", "/home/user", NULL};
	int		saved_stdout;
	int		tmp_fd;
	int		result;

	env_list = NULL;
	env_list = &env_node;
	// Redirect stdout
	saved_stdout = dup(STDOUT_FILENO);
	tmp_fd = open("test_output", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(tmp_fd, STDOUT_FILENO);
	result = rh_env(args, envp, &env_list);
	// Restore stdout
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(tmp_fd);
	ck_assert_int_eq(result, EXIT_SUCCESS);
}
END_TEST

START_TEST(test_rh_env_g_option)
{
	char	*args[] = {"env", "-g", NULL};
	char	*envp[] = {"PATH=/bin", NULL};
	t_env	*env_list;
	int		result;

	env_list = NULL;
	result = rh_env(args, envp, &env_list);
	ck_assert_int_eq(result, EXIT_SUCCESS);
}
END_TEST

START_TEST(test_rh_env_invalid_option)
{
	char	*args[] = {"env", "-x", NULL};
	char	*envp[] = {"PATH=/bin", NULL};
	t_env	*env_list;
	int		result;

	env_list = NULL;
	result = rh_env(args, envp, &env_list);
	ck_assert_int_eq(result, EXIT_SUCCESS);
}
END_TEST

Suite	*builtin_env_test(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("env");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_rh_env_no_args);
	tcase_add_test(tc_core, test_rh_env_g_option);
	tcase_add_test(tc_core, test_rh_env_invalid_option);
	suite_add_tcase(s, tc_core);
	return (s);
}
