#include "../tests.h"

// Mock function to capture output
// Mock function to capture output
char	*captured_output = NULL;

// Create weak alias to override original writing function
__attribute__((weak)) int writing(char *str);

int	writing(char *str)
{
	char	*new_output;

	if (captured_output == NULL)
	{
		captured_output = strdup(str);
	}
	else
	{
		new_output = malloc(strlen(captured_output) + strlen(str) + 1);
		strcpy(new_output, captured_output);
		strcat(new_output, str);
		free(captured_output);
		captured_output = new_output;
	}
	return (0);
}

void	reset_captured_output(void)
{
	if (captured_output)
	{
		free(captured_output);
		captured_output = NULL;
	}
}

START_TEST(test_rh_echo_no_args)
{
	char	*args[] = {"echo", NULL};
	int		result;

	reset_captured_output();
	result = rh_echo(args);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_str_eq(captured_output, "\n");
}
END_TEST

START_TEST(test_rh_echo_with_args)
{
	char	*args[] = {"echo", "Hello", "world", NULL};
	int		result;

	reset_captured_output();
	result = rh_echo(args);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_str_eq(captured_output, "Hello world\n");
}
END_TEST

START_TEST(test_rh_echo_with_n_option)
{
	char	*args[] = {"echo", "-n", "Hello", "world", NULL};
	int		result;

	reset_captured_output();
	result = rh_echo(args);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_str_eq(captured_output, "Hello world");
}
END_TEST

START_TEST(test_rh_echo_with_multiple_n_options)
{
	char	*args[] = {"echo", "-n", "-n", "Hello", "world", NULL};
	int		result;

	reset_captured_output();
	result = rh_echo(args);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_str_eq(captured_output, "Hello world");
}
END_TEST

Suite	*builtin_echo_test(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("echo");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_rh_echo_no_args);
	tcase_add_test(tc_core, test_rh_echo_with_args);
	tcase_add_test(tc_core, test_rh_echo_with_n_option);
	tcase_add_test(tc_core, test_rh_echo_with_multiple_n_options);
	suite_add_tcase(s, tc_core);
	return (s);
}
