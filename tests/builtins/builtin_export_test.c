#include "../tests.h"

START_TEST(test_rh_export_no_args)
{
	t_env	*env_list;
	char	*args[] = {"export", NULL};
	int		result;

	env_list = create_env_var("TEST", "value");
	result = rh_export(args, &env_list);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	// Assuming print_sortedenvlist prints the environment list
	free_env_list(env_list);
}
END_TEST

START_TEST(test_rh_export_add_new_var)
{
	t_env	*env_list;
	char	*args[] = {"export", "NEW_VAR=new_value", NULL};
	int		result;

	env_list = NULL;
	result = rh_export(args, &env_list);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_ptr_nonnull(env_list);
	ck_assert_str_eq(env_list->key, "NEW_VAR");
	ck_assert_str_eq(env_list->val, "new_value");
	free_env_list(env_list);
}
END_TEST

START_TEST(test_rh_export_update_var)
{
	t_env	*env_list;
	char	*args[] = {"export", "TEST=new_value", NULL};
	int		result;

	env_list = create_env_var("TEST", "old_value");
	result = rh_export(args, &env_list);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_ptr_nonnull(env_list);
	ck_assert_str_eq(env_list->key, "TEST");
	ck_assert_str_eq(env_list->val, "new_value");
	free_env_list(env_list);
}
END_TEST

START_TEST(test_rh_export_add_var_without_value)
{
	t_env	*env_list;
	char	*args[] = {"export", "NEW_VAR", NULL};
	int		result;

	env_list = NULL;
	result = rh_export(args, &env_list);
	ck_assert_int_eq(result, EXIT_SUCCESS);
	ck_assert_ptr_nonnull(env_list);
	ck_assert_str_eq(env_list->key, "NEW_VAR");
	ck_assert_ptr_null(env_list->val);
	free_env_list(env_list);
}
END_TEST

Suite	*builtin_export_test(void)
{
	Suite	*s;
	TCase	*tc_core;

	s = suite_create("export");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_rh_export_no_args);
	tcase_add_test(tc_core, test_rh_export_add_new_var);
	tcase_add_test(tc_core, test_rh_export_update_var);
	tcase_add_test(tc_core, test_rh_export_add_var_without_value);
	suite_add_tcase(s, tc_core);
	return (s);
}
