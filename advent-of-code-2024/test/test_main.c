#include "aux.h"
#include "day_1.h"
#include "day_2.h"
#include "day_3.h"
#include "day_4.h"

#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file test_main.c
 * @brief Entry point for running unit tests using the CUnit testing framework.
 *
 * This file sets up the CUnit testing framework, including test registry
 * initialization, suite and test case registration, and the execution of all
 * registered tests. It ensures that errors are logged appropriately and
 * terminates the test run if any setup or execution fails.
 */

/* Function prototypes */
static void test_one(void);
static void test_two(void);
static void test_three(void);
static void test_four(void);

/**
 * @brief Main function to initialize and execute CUnit tests.
 *
 * @return 0 on success, or a non-zero error code on failure.
 */
int
main (void)
{
    int retval;
    CU_basic_set_mode(CU_BRM_VERBOSE);

    retval = CU_initialize_registry();
    if (CUE_SUCCESS != retval)
    {
        ERROR_LOG(
            "Failed CU_initialize_registry: unable to initialize CUnit "
            "registry");
        goto CLEANUP;
    }

    CU_pSuite suite = CU_add_suite("Testing Suite", NULL, NULL);
    if (NULL == suite)
    {
        ERROR_LOG("Failed CU_add_suite: unable to create CUnit test suite");
        goto CLEANUP;
    }

    // Add test cases to the suite as needed
    if (NULL == CU_add_test(suite, "test_one", test_one))
    {
        ERROR_LOG("Failed CU_add_test: unable to add test_one");
    }

    if (NULL == CU_add_test(suite, "test_two", test_two))
    {
        ERROR_LOG("Failed CU_add_test: unable to add test_two");
    }

    if (NULL == CU_add_test(suite, "test_three", test_three))
    {
        ERROR_LOG("Failed CU_add_test: unable to add test_three");
    }

    if (NULL == CU_add_test(suite, "test_four", test_four))
    {
        ERROR_LOG("Failed CU_add_test: unable to add test_four");
    }

    retval = CU_basic_run_tests();
    if (CUE_SUCCESS != retval)
    {
        ERROR_LOG("Failed CU_basic_run_tests: unable to run tests");
        goto CLEANUP;
    }

    if (CU_get_number_of_failures() > 0)
    {
        exit(EXIT_FAILURE);
    }

CLEANUP:
    CU_cleanup_registry();
    return retval;
}

/**
 * @brief Test case for validating the functionality of the `day_1` function.
 */
static void
test_one (void)
{
    int expected_result[] = { 11, 31 }; /**< Expected results for comparison */
    int actual_result[]   = { 0, 0 };   /**< Array to store actual results */

    CU_ASSERT_EQUAL_FATAL(day_1("data/example_1.txt", actual_result), 0);
    CU_ASSERT_EQUAL_FATAL(actual_result[0], expected_result[0]);
    CU_ASSERT_EQUAL_FATAL(actual_result[1], expected_result[1]);
}

/**
 * @brief Test case for validating the functionality of the `day_2` function.
 */
static void
test_two (void)
{
    int expected_result[] = { 2, 4 }; /**< Expected results for comparison */
    int actual_result[]   = { 0, 0 }; /**< Array to store actual results */

    CU_ASSERT_EQUAL_FATAL(day_2("data/example_2.txt", actual_result), 0);
    CU_ASSERT_EQUAL_FATAL(actual_result[0], expected_result[0]);
    CU_ASSERT_EQUAL_FATAL(actual_result[1], expected_result[1]);
}

/**
 * @brief Test case for validating the functionality of the `day_3` function.
 */
static void
test_three (void)
{
    int expected_result[] = { 161, 48 }; /**< Expected results for comparison */
    int actual_result[]   = { 0, 0 };    /**< Array to store actual results */

    CU_ASSERT_EQUAL_FATAL(day_3("data/example_3.txt", actual_result), 0);
    CU_ASSERT_EQUAL_FATAL(actual_result[0], expected_result[0]);
    CU_ASSERT_EQUAL_FATAL(actual_result[1], expected_result[1]);
}

/**
 * @brief Test case for validating the functionality of the `day_4` function.
 */
static void
test_four (void)
{
    int expected_result[] = { 18, 9 }; /**< Expected results for comparison */
    int actual_result[]   = { 0, 0 };  /**< Array to store actual results */

    CU_ASSERT_EQUAL_FATAL(day_4("data/example_4.txt", actual_result), 0);
    CU_ASSERT_EQUAL_FATAL(actual_result[0], expected_result[0]);
    CU_ASSERT_EQUAL_FATAL(actual_result[1], expected_result[1]);
}

/*** end of file ***/
