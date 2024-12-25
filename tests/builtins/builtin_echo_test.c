#include "../tests.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	*capture_stdout(char *args[], int *exit_code)
{
	int		pipefd[2];
	int		saved_stdout;
	char	buffer[1024];
	ssize_t	n;
	char	*output;

	// Create pipe
	pipe(pipefd);
	// Save current stdout
	saved_stdout = dup(STDOUT_FILENO);
	// Redirect stdout to pipe
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	// Call the function under test
	*exit_code = rh_echo(args);
	// Restore stdout
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	// Read from pipe
	memset(buffer, 0, sizeof(buffer));
	n = read(pipefd[0], buffer, sizeof(buffer) - 1);
	close(pipefd[0]);
	// Duplicate output
	if (n > 0)
		buffer[n] = '\0';
	else
		buffer[0] = '\0';
	output = strdup(buffer);
	return (output);
}

START_TEST(test_rh_echo_no_args)
{
	char	*args[] = {"echo", NULL};
	int		status;
	char	*out;

	out = capture_stdout(args, &status);
	ck_assert_int_eq(status, EXIT_SUCCESS);
	ck_assert_str_eq(out, "\n");
	free(out);
}
END_TEST

START_TEST(test_rh_echo_with_args)
{
	char	*args[] = {"echo", "Hello", "world", NULL};
	int		status;
	char	*out;

	out = capture_stdout(args, &status);
	ck_assert_int_eq(status, EXIT_SUCCESS);
	ck_assert_str_eq(out, "Hello world\n");
	free(out);
}
END_TEST

// START_TEST(test_rh_echo_with_env_var)
// {
// 	char	*args[] = {"echo", "$HOME", NULL};
// 	int		status;
// 	char	*out;

// 	out = capture_stdout(args, &status);
// 	ck_assert_int_eq(status, EXIT_SUCCESS);
// 	ck_assert_str_eq(out, "$HOME\n");
// 	free(out);
// }

// END_TEST

Suite	*builtin_echo_test(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("echo");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_rh_echo_no_args);
	tcase_add_test(tc_core, test_rh_echo_with_args);
	suite_add_tcase(s, tc_core);
	return (s);
}
