#include "../tests.h"

START_TEST(test_remove_envvar_success)
{
	t_env	*env_list;
	int		result;

	env_list = create_env_var("TEST", "value");
	env_list->next = create_env_var("REMOVE_ME", "value2");
	result = remove_envvar("REMOVE_ME", &env_list);
	ck_assert_int_eq(result, 0);
	ck_assert_ptr_nonnull(env_list);
	ck_assert_str_eq(env_list->key, "TEST");
	ck_assert_ptr_null(env_list->next);
	free_env_list(env_list);
}
END_TEST

START_TEST(test_remove_envvar_not_found)
{
	t_env	*env_list;
	int		result;

	env_list = create_env_var("TEST", "value");
	result = remove_envvar("NOT_FOUND", &env_list);
	ck_assert_int_eq(result, -1);
	ck_assert_ptr_nonnull(env_list);
	ck_assert_str_eq(env_list->key, "TEST");
	ck_assert_ptr_null(env_list->next);
	free_env_list(env_list);
}
END_TEST

START_TEST(test_rh_unset_success)
{
	t_env	*env_list;
	char	*args[] = {"unset", "REMOVE_ME", NULL};
	int		result;

	env_list = create_env_var("TEST", "value");
	env_list->next = create_env_var("REMOVE_ME", "value2");
	result = rh_unset(args, &env_list);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_ptr_nonnull(env_list);
	ck_assert_str_eq(env_list->key, "TEST");
	ck_assert_ptr_null(env_list->next);
	free_env_list(env_list);
}
END_TEST

START_TEST(test_rh_unset_no_args)
{
	t_env	*env_list;
	char	*args[] = {"unset", NULL};
	int		result;

	env_list = create_env_var("TEST", "value");
	result = rh_unset(args, &env_list);
	ck_assert_int_eq(result, 1);
	ck_assert_ptr_nonnull(env_list);
	ck_assert_str_eq(env_list->key, "TEST");
	ck_assert_ptr_null(env_list->next);
	free_env_list(env_list);
}
END_TEST

Suite	*builtin_unset_test(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("unset");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_remove_envvar_success);
	tcase_add_test(tc_core, test_remove_envvar_not_found);
	tcase_add_test(tc_core, test_rh_unset_success);
	tcase_add_test(tc_core, test_rh_unset_no_args);
	suite_add_tcase(s, tc_core);
	return (s);
}
