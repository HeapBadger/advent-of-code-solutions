#include "aux.h"
#include "day_0.h"

#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file test_main.c
 * @brief Entry point for running unit tests using the CUnit testing framework.
 *
 * This file initializes the CUnit registry, sets up test suites and test cases,
 * and executes all registered tests.
 */

static void test_zero(void);

/**
 * @brief Main function for setting up and executing CUnit tests.
 *
 * The function initializes the CUnit registry, creates test suites, registers
 * test cases, and runs all tests. It uses the `ERROR_LOG` macro for error
 * reporting.
 *
 * @return 0 on success, non-zero error code on failure.
 */
int main(void) {
  int retval;
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // exit failure if any test fails (for pipeline)
  if (0 < CU_get_number_of_failures()) {
    exit(EXIT_FAILURE);
  }

  // initialize CUnit registry
  retval = CU_initialize_registry();

  if (CUE_SUCCESS != retval) {
    ERROR_LOG("failed to initialize CUnit registry");
    goto CLEANUP;
  }

  // create a test suite
  CU_pSuite suite = NULL;
  suite = CU_add_suite("testing-suite", 0, 0);

  if (NULL == suite) {
    ERROR_LOG("failed to create CUnit test suite");
    goto CLEANUP;
  }

  // add test cases to the suite
  if (NULL == (CU_add_test(suite, "test_zero", test_zero))) {
    ERROR_LOG("failed to add test_zero to suite");
  }

  // add additional tests here as needed.

  // run all tests in the registry
  retval = CU_basic_run_tests();

  if (CUE_SUCCESS != retval) {
    ERROR_LOG("failed to run test suites");
    goto CLEANUP;
  }

CLEANUP:
  // clean up the CUnit registry
  CU_cleanup_registry();
  return retval;
}

/**
 * @brief Test case for validating the functionality of `day_0` function.
 */
static void test_zero(void) {
  int expected_result[] = {142, 281};
  int actual_result[] = {0, 0};

  CU_ASSERT_EQUAL_FATAL(day_0("data/example_0.txt", actual_result), 0);
  CU_ASSERT_EQUAL_FATAL(actual_result[0], expected_result[0]);
  CU_ASSERT_EQUAL_FATAL(actual_result[1], expected_result[1]);
  return;
}
