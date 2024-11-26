#include <check.h>
#include <stdlib.h>

// Declare the suite functions from other test files
Suite	*lexer_grouping_suite(void);
Suite	*lexer_operator_suite(void);
Suite	*lexer_quote_suite(void);

	int main(void)
{
	int number_failed;
	SRunner *sr;

	// Create a new test runner
	sr = srunner_create(NULL);

	// Add suites to the test runner
	srunner_add_suite(sr, lexer_grouping_suite());
	srunner_add_suite(sr, lexer_operator_suite());
	srunner_add_suite(sr, lexer_quote_suite());

	// If you have more suites, add them here
	// srunner_add_suite(sr, another_suite());

	// Run all tests
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	// Return the number of failed tests as the exit code
	return ((number_failed == 0) ? 0 : 1);
}