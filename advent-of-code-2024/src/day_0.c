#include "day_0.h"
#include "aux.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_0.c
 * @brief Implementation of a day_0 challenge.
 *
 * Provides the implementation of the functions declared in header file.
 */

#define BUFFER_SIZE 256
#define EXIT_DNE -1

static int calibration_one(const char *line);
static int calibration_two(const char *line);
static void extract_digits(const char *buffer, char *digits);

/**
 * @brief See header file for details.
 */
int day_0(const char *filename, int result[2]) {
  int sum;
  FILE *fp;
  char line[BUFFER_SIZE];

  ///// PART ONE /////
  sum = 0;
  fp = fopen(filename, "r");

  if (NULL == fp) {
    ERROR_LOG("unable to open file");
    return EXIT_FAILURE;
  } else {
    while (NULL != fgets(line, sizeof(line), fp)) {
      sum += calibration_one(line);
    }

    fclose(fp);
    result[0] = sum;
  }

  ///// PART TWO /////
  sum = 0;
  fp = fopen(filename, "r");

  if (NULL == fp) {
    ERROR_LOG("unable to open file");
    return EXIT_FAILURE;
  } else {
    while (NULL != fgets(line, sizeof(line), fp)) {
      sum += calibration_two(line);
    }

    fclose(fp);
    result[1] = sum;
  }

  return EXIT_SUCCESS;
}

/**
 * @brief Finds the calibration value from a string.
 *
 * Calibration value is found by combining the first and
 * last digit into a single two-digit number.
 *
 * @example:
 *  a1b2c3d4e5f  = 15
 *  treb7uchet   = 77
 *
 * @param line Line of text to be calibrated.
 * @return Final calibrated number.
 */
static int calibration_one(const char *line) {
  // extra space for null-terminator
  char calibrated_digit[3] = {'\0', '\0', '\0'};

  for (int i = 0; line[i] != '\0'; i++) {
    if ((isdigit((unsigned char)line[i])) && ('\0' == calibrated_digit[0])) {
      calibrated_digit[0] = line[i];
      calibrated_digit[1] = line[i];
    } else if (isdigit(line[i])) {
      calibrated_digit[1] = line[i];
    }
  }

  // convert the character array into an integer
  return (calibrated_digit[0] - '0') * 10 + (calibrated_digit[1] - '0');
}

/**
 * @brief Finds the calibration value from a string.
 *
 * Calibration value is found by combining the first and
 * last digit into a single two-digit number, including spelled
 * out words.
 *
 * @example:
 *  two1nine          = 29
 *  4nineeightseven2  = 42
 *
 * @param line Line of text to be calibrated.
 * @return Final calibrated number.
 */
static int calibration_two(const char *line) {
  char *found_digits = calloc(BUFFER_SIZE, sizeof(char));
  int result = EXIT_DNE;

  if (NULL != found_digits)
  {
    extract_digits(line, found_digits);
    result = (found_digits[0] - '0') + (found_digits[strlen(found_digits) - 1] - '0');
    printf("line: %sDigits: %s\tresult: %d\n\n", line, found_digits, result);
    free(found_digits);
  }

  return result;
}

static void extract_digits(const char *buffer, char *digits) {
  const char *letter_map[] = {"zero", "one", "two",   "three", "four",
                              "five", "six", "seven", "eight", "nine"};
  const size_t word_lengths[] = {4, 3, 3, 5, 4, 4, 3, 5, 5, 4};
  const int num_elements = sizeof(letter_map) / sizeof(letter_map[0]);

  while ('\0' != *buffer) {
    // check if the current character is a digit
    if (('\0' <= *buffer) && ('9' >= *buffer)) {
      *digits++ = *buffer++;
      continue;
    }

    // check for spelled-out numbers
    int matched = 0;

    for (int i = 0; i < num_elements; i++) {
      if (0 == strncmp(buffer, letter_map[i], word_lengths[i])) {
        *digits++ = i + '0';
        buffer += word_lengths[i];
        matched = 1;
        break;
      }
    }

    // if no match, move to the next character
    if (!matched) {
      buffer++;
    }
  }

  *digits = '\0'; // null-terminate the result string
}