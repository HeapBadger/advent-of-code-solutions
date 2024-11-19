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
static void check_spelled_digit_recursive(const char *buffer, int result[]);

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
  // extra space for null-terminator; 2-digit result
  char calibrated_digit[3] = {'\0', '\0', '\0'};
  printf("\nline: %s\n", line);

  // buffer for partial_line
  char partial_line[BUFFER_SIZE];
  memset(partial_line, '\0', sizeof(partial_line));
  int buff_i = 0;
  int result[] = {-1, -1};

  for (int i = 0; line[i] != '\0'; i++) {
    if ((isdigit((unsigned char)line[i]))) {
      result[0] = -1;
      result[1] = -1;
      check_spelled_digit_recursive(partial_line, result);
      printf("letter digits found: %d\t%d\n", result[0], result[1]);
      printf("digit found: %d\n", (line[i] - '0'));
      buff_i = 0;
      memset(partial_line, '\0', sizeof(partial_line));

      if (EXIT_DNE == calibrated_digit[0])
      {
        if (EXIT_DNE != result[0])
        {
          calibrated_digit[0] = result[0];
          calibrated_digit[1] = line[i];
        }
        else
        {
          calibrated_digit[0] = line[i];
          calibrated_digit[1] = line[i];
        }
      }
      else 
      {
        calibrated_digit[1] = line[i];
      }
    }

    partial_line[buff_i] = line[i];
    buff_i++;
  }

  // check buffer one more time for partial_line
  result[0] = -1;
  result[1] = -1;
  check_spelled_digit_recursive(partial_line, result);
  printf("letter digits found: %d\t%d\n", result[0], result[1]);

  // convert the character array into an integer
  printf("Calidbration: %d\t%d\n", calibrated_digit[0], calibrated_digit[1]);
  return 0;
}

/**
 * @brief Checks if a spelled-out number (e.g., "zero", "one", ...) matches a
 *        digit, and stores any matching digit found in the result array.
 *
 * @param buffer A null-terminated string representing the spelled-out number.
 *               It should be a single word (e.g., "zero", "one", etc.).
 *
 * @param result A 2-element array where the first element will store the first
 *               matching digit, and the second element will store any final
 *               subsequent match.
 */
static void check_spelled_digit_recursive(const char *buffer, int result[2]) {
  if (*buffer == '\0') {
    return EXIT_DNE;
  }

  // map of spelled-out number words to corresponding digits
  const char *letter_map[] = {"zero", "one", "two",   "three", "four",
                              "five", "six", "seven", "eight", "nine"};
  const int num_elements = sizeof(letter_map) / sizeof(letter_map[0]);

  // iterate through the letter_map to find a match
  for (int i = 0; i < num_elements; i++) {
    if (strlen(buffer) >= strlen(letter_map[i]) &&
        strncmp(buffer, letter_map[i], strlen(letter_map[i])) == 0) {
      if (EXIT_DNE == result[0]) {
        result[0] = i;
      } else {
        result[1] = i;
      }
    }
  }

  // recursively check the next part of the buffer
  return check_spelled_digit_recursive(buffer + 1, result);
}
