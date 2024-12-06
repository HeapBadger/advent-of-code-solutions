#include "day_1.h"
#include "aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_1.c
 * @brief Implementation of the day_1 challenge.
 *
 * Provides functions for processing integer pairs from a file
 * and storing them in dynamically resizable arrays.
 */

/* Macros */
#define BUFFER_SIZE (256)      ///< Maximum line size for file input.
#define INITIAL_LIST_SIZE (10) ///< Initial size of the arrays.
#define ELE_DNE (-1)           ///< Marker for an empty array element.

/**
 * @brief Structure to hold organized arrays of integers.
 */
typedef struct {
  int max_size;  ///< Maximum size of the arrays.
  int curr_idx;  ///< Current index for inserting elements.
  int *list_one; ///< First array of integers.
  int *list_two; ///< Second array of integers.
} SortedArrays;

/* Function Prototypes */
void bubble_sort(int numbers[], int size);
static int similarity_score(int num, const int *array, int size);
static int extract_digits(const char *line, int digits[2]);
static SortedArrays *sortedarrays_initialize(void);
static void sortedarrays_destroy(SortedArrays *array);
static int sortedarrays_add(SortedArrays *array, const int elements[2]);
static int sortedarrays_resize(SortedArrays *array);

/**
 * @brief Processes the file and extracts integer pairs.
 *
 * @param filename Path to the input file.
 * @param result Array to store the results.
 * @return int EXIT_SUCCESS on success, otherwise EXIT_FAILURE.
 */
int day_1(const char *filename, int result[2]) {
  FILE *fp = NULL;
  SortedArrays *array = NULL;
  char line[BUFFER_SIZE] = {0};
  int sum = 0;

  if ((filename == NULL) || (result == NULL)) {
    ERROR_LOG("Invalid input to day_1");
    return EXIT_FAILURE;
  }

  fp = fopen(filename, "r");
  if (fp == NULL) {
    ERROR_LOG("Unable to open file");
    return EXIT_FAILURE;
  }

  array = sortedarrays_initialize();
  if (array == NULL) {
    fclose(fp);
    return EXIT_FAILURE;
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    int digits[2] = {ELE_DNE, ELE_DNE};
    if (extract_digits(line, digits) == EXIT_SUCCESS) {
      if (sortedarrays_add(array, digits) == EXIT_FAILURE) {
        ERROR_LOG("Failed to add elements to array");
        break;
      }
    }
  }

  fclose(fp);

  // Part One
  bubble_sort(array->list_one, array->curr_idx);
  bubble_sort(array->list_two, array->curr_idx);

  for (int idx = 0; idx < array->curr_idx; idx++) {
    sum += abs(array->list_one[idx] - array->list_two[idx]);
  }

  result[0] = sum;

  // Part Two
  sum = 0;

  for (int idx = 0; idx < array->max_size; idx++) {
    sum += similarity_score(array->list_one[idx], array->list_two,
                            array->max_size);
  }

  result[1] = sum;

  sortedarrays_destroy(array);

  return EXIT_SUCCESS;
}

/**
 * @brief Calculates a similarity score for a given integer.
 *
 * The score is calculated as the product of the integer (`num`) and its
 * frequency in the array (`array`). The array must be sorted in ascending order
 * and contain only non-negative integers. Elements with the value `ELE_DNE` are
 * skipped during the calculation.
 *
 * @param num The integer for which the similarity score is calculated. Must be
 * non-negative.
 * @param array Pointer to an array of integers. Must be sorted in ascending
 * order and contain only non-negative integers.
 * @param size The size of the array. Must be non-negative.
 *
 * @return The similarity score if successful, or 0 if the integer is not found
 * or the input parameters are invalid.
 */
static int similarity_score(int num, const int *array, int size) {
  int idx;
  int count = 0;

  if (num < 0 || array == NULL || size < 0) {
    return 0;
  }

  for (idx = 0; idx < size; idx++) {
    if (array[idx] == ELE_DNE) {
      continue;
    } else if (array[idx] > num) {
      break;
    } else if (array[idx] == num) {
      count++;
    }
  }

  return count * num;
}

/**
 * @brief Sorts an array of integers in ascending order using bubble sort.
 *
 * @param numbers Pointer to the array of integers.
 * @param size Number of elements in the array.
 */
void bubble_sort(int numbers[], int size) {
  int i, j, tmp;

  if ((numbers == NULL) || (size <= 0)) {
    ERROR_LOG("Invalid array or size");
    return;
  }

  for (i = size - 1; i >= 0; i--) {
    for (j = 1; j <= i; j++) {
      if (numbers[j - 1] > numbers[j]) {
        tmp = numbers[j - 1];
        numbers[j - 1] = numbers[j];
        numbers[j] = tmp;
      }
    }
  }
}

/**
 * @brief Extracts two integers from a line of text.
 *
 * @param line Input line of text.
 * @param digits Array to store the extracted integers.
 * @return int EXIT_SUCCESS if successful, otherwise EXIT_FAILURE.
 */
static int extract_digits(const char *line, int digits[2]) {
  if ((line == NULL) || (digits == NULL)) {
    ERROR_LOG("Invalid input to extract_digits");
    return EXIT_FAILURE;
  }

  if (sscanf(line, "%d %d", &digits[0], &digits[1]) != 2) {
    ERROR_LOG("Failed to parse integers");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/**
 * @brief Initializes a new SortedArrays structure.
 *
 * @return Pointer to the initialized structure, or NULL on failure.
 */
static SortedArrays *sortedarrays_initialize(void) {
    SortedArrays *array = calloc(1, sizeof(SortedArrays));
    if (array == NULL) {
        ERROR_LOG("Failed to allocate memory for SortedArrays");
        return NULL;
    }

    array->list_one = calloc(INITIAL_LIST_SIZE, sizeof(int));
    array->list_two = calloc(INITIAL_LIST_SIZE, sizeof(int));

    if ((array->list_one == NULL) || (array->list_two == NULL)) {
        ERROR_LOG("Failed to allocate memory for arrays");
        sortedarrays_destroy(array);
        return NULL;
    }

    // Initialize arrays to ELE_DNE
    for (int i = 0; i < INITIAL_LIST_SIZE; i++) {
        array->list_one[i] = ELE_DNE;
        array->list_two[i] = ELE_DNE;
    }

    array->max_size = INITIAL_LIST_SIZE;

    return array;
}

/**
 * @brief Resizes the arrays in the SortedArrays structure.
 *
 * @param array Pointer to the SortedArrays structure.
 * @return int EXIT_SUCCESS on success, otherwise EXIT_FAILURE.
 */
static int sortedarrays_resize(SortedArrays *array) {
    int new_size = array->max_size * 2;
    int *new_list_one = realloc(array->list_one, new_size * sizeof(int));
    int *new_list_two = realloc(array->list_two, new_size * sizeof(int));

    if ((new_list_one == NULL) || (new_list_two == NULL)) {
        ERROR_LOG("Failed to resize arrays");
        return EXIT_FAILURE;
    }

    // Set new elements to ELE_DNE
    for (int i = array->max_size; i < new_size; i++) {
        new_list_one[i] = ELE_DNE;
        new_list_two[i] = ELE_DNE;
    }

    array->list_one = new_list_one;
    array->list_two = new_list_two;
    array->max_size = new_size;

    return EXIT_SUCCESS;
}

/**
 * @brief Frees the memory associated with a SortedArrays structure.
 *
 * @param array Pointer to the SortedArrays structure to free.
 */
static void sortedarrays_destroy(SortedArrays *array) {
  if (array != NULL) {
    free(array->list_one);
    free(array->list_two);
    free(array);
  }
}

/**
 * @brief Adds a pair of integers to the SortedArrays structure.
 *
 * @param array Pointer to the SortedArrays structure.
 * @param elements Array containing the two integers to add.
 * @return int EXIT_SUCCESS on success, otherwise EXIT_FAILURE.
 */
static int sortedarrays_add(SortedArrays *array, const int elements[2]) {
  if ((array == NULL) || (elements == NULL)) {
    ERROR_LOG("Invalid input to sortedarrays_add");
    return EXIT_FAILURE;
  }

  if (array->curr_idx >= array->max_size) {
    if (sortedarrays_resize(array) == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
  }

  array->list_one[array->curr_idx] = elements[0];
  array->list_two[array->curr_idx] = elements[1];
  array->curr_idx++;

  return EXIT_SUCCESS;
}
