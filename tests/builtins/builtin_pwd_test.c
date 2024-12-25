
#include "../../src/minishell.h"
#include "../../src/parser/parser.h"
#include <check.h>

START_TEST(test_pwd_success)
{
	char	*expected;
	int		ret;

	expected = getcwd(NULL, 0);
	ret = rh_pwd();
	ck_assert_int_eq(ret, EXIT_SUCCESS);
	free(expected);
}
END_TEST

START_TEST(test_cd_success)
{
	char	*old_dir;
	char	*home;
	int		ret;

	old_dir = getcwd(NULL, 0);
	home = getenv("HOME");
	ret = rh_cd(home);
	ck_assert_int_eq(ret, EXIT_SUCCESS);
	ret = rh_cd(old_dir);
	ck_assert_int_eq(ret, EXIT_SUCCESS);
	free(old_dir);
}
END_TEST

START_TEST(test_cd_null_path)
{
	char	*old_dir;
	int		ret;

	old_dir = getcwd(NULL, 0);
	ret = rh_cd(NULL);
	ck_assert_int_eq(ret, EXIT_SUCCESS);
	ret = rh_cd(old_dir);
	ck_assert_int_eq(ret, EXIT_SUCCESS);
	free(old_dir);
}
END_TEST

START_TEST(test_cd_invalid_path)
{
	int	ret;

	ret = rh_cd("/nonexistent/path");
	ck_assert_int_eq(ret, EXIT_FAILURE);
}
END_TEST

Suite	*builtin_pwd_test(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("pwd");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_pwd_success);
	tcase_add_test(tc_core, test_cd_success);
	tcase_add_test(tc_core, test_cd_null_path);
	tcase_add_test(tc_core, test_cd_invalid_path);
	suite_add_tcase(s, tc_core);
	return (s);
}
