#include <check.h>
#include <stdlib.h>

// Existing suite declarations
Suite	*lexer_grouping_suite(void);
Suite	*lexer_operator_suite(void);
Suite	*lexer_quote_suite(void);
Suite	*lexer_redirection_suite(void);
Suite	*lexer_word_suite(void);

// New parser suite declarations
Suite	*parser_simple_command_suite(void);
Suite	*parser_pipe_suite(void);
Suite	*parser_redirection_suite(void);
Suite	*parser_logical_suite(void);

// Builtins Suite
Suite	*builtin_pwd_test(void);
Suite	*builtin_unset_test(void);

int	main(void)
{
	int		number_failed;
	SRunner	*sr;

	sr = srunner_create(NULL);
	// Add lexer suites
	srunner_add_suite(sr, lexer_grouping_suite());
	srunner_add_suite(sr, lexer_operator_suite());
	srunner_add_suite(sr, lexer_quote_suite());
	srunner_add_suite(sr, lexer_redirection_suite());
	srunner_add_suite(sr, lexer_word_suite());
	// Add parser suites
	srunner_add_suite(sr, parser_simple_command_suite());
	srunner_add_suite(sr, parser_pipe_suite());
	srunner_add_suite(sr, parser_redirection_suite());
	srunner_add_suite(sr, parser_logical_suite());
	// Add builtins suites
	srunner_add_suite(sr, builtin_pwd_test());
	srunner_add_suite(sr, builtin_unset_test());
	// Run all the suites
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return ((number_failed == 0) ? 0 : 1);
}
