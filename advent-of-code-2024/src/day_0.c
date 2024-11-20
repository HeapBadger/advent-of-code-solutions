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
// static void check_digit_recursive(const char *buffer, char result[3]);
static void extract_digits_recursive(const char *buffer, char *digits);

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

  // buffer for partial_line
  char partial_line[BUFFER_SIZE];
  memset(partial_line, '\0', sizeof(partial_line));
  int buff_i = 0;
  int result[] = {-1, -1};

  extract_digits_recursive(line, calibrated_digit);
  // check_digit_recursive(line, calibrated_digit);
  // calibrated_digit[0] = result[0];
  // calibrated_digit[1] = result[1];
  printf("line: %s\tDigits: %c, %c, %d\n", line, calibrated_digit[0], calibrated_digit[1], (calibrated_digit[0] - '0') * 10 + (calibrated_digit[1] - '0'));
  // convert the character array into an integer
  return (calibrated_digit[0] - '0') * 10 + (calibrated_digit[1] - '0');
}

/**
 * @brief Recursively extracts digits from a mixed string containing numeric digits
 *        and spelled-out numbers, preserving the order of appearance.
 *
 * @param buffer A null-terminated string containing digits and spelled-out numbers.
 * @param digits An output string buffer where extracted digits will be appended.
 *               It should be large enough to hold all extracted digits plus a null terminator.
 */
static void extract_digits_recursive(const char *buffer, char *digits) {
    // Base case: End of the string
    if (*buffer == '\0') {
        return;
    }

    // Map of spelled-out number words to corresponding digits
    const char *letter_map[] = {"zero", "one", "two",   "three", "four",
                                "five", "six", "seven", "eight", "nine"};
    const int num_elements = sizeof(letter_map) / sizeof(letter_map[0]);

    // Check if the current character is a digit
    if (*buffer >= '0' && *buffer <= '9') {
        *digits = *buffer;  // Append digit to the output
        extract_digits_recursive(buffer + 1, digits + 1);
        return;
    }

    // Check for spelled-out numbers
    for (int i = 0; i < num_elements; i++) {
        size_t word_len = strlen(letter_map[i]);
        if (strncmp(buffer, letter_map[i], word_len) == 0) {
            *digits = i + '0'; // Append digit to the output
            extract_digits_recursive(buffer + word_len, digits + 1);
            return;
        }
    }

    // If no match, move to the next character
    extract_digits_recursive(buffer + 1, digits);
}

// /**
//  * @brief Checks if a spelled-out number (e.g., "zero", "one", ...) matches a
//  *        digit, and stores any matching digit found in the result array.
//  *
//  * @param buffer A null-terminated string representing the spelled-out number.
//  *               It should be a single word (e.g., "zero", "one", etc.).
//  *
//  * @param result A 2-element array where the first element will store the first
//  *               matching digit, and the second element will store any final
//  *               subsequent match.
//  */
// static void check_digit_recursive(const char *buffer, char calibrated_digit[3]) {
//   if (*buffer == '\0') {
//     return;
//   }

//   // map of spelled-out number words to corresponding digits
//   const char *letter_map[] = {"zero", "one", "two",   "three", "four",
//                               "five", "six", "seven", "eight", "nine"};
//   const int num_elements = sizeof(letter_map) / sizeof(letter_map[0]);

//   // check if current character is a digit
//   if (*buffer >= '0' && *buffer <= '9') {
//     if ('\0' == calibrated_digit[0]) {
//       calibrated_digit[0] = *buffer;
//       calibrated_digit[1] = *buffer;
//     } else {
//       calibrated_digit[1] = *buffer;
//     }

//     return check_digit_recursive(buffer + 1, calibrated_digit);
//   }

//   // iterate through the letter_map to find a match
//   for (int i = 0; i < num_elements; i++) {
//     if (strlen(buffer) >= strlen(letter_map[i]) &&
//         strncmp(buffer, letter_map[i], strlen(letter_map[i])) == 0) {
//       if ('\0' == calibrated_digit[0]) {
//         calibrated_digit[0] = i + '0';
//         calibrated_digit[1] = i + '0';
//       } else {
//         calibrated_digit[1] = i + '0';
//       }
//     }
//   }

//   // recursively check the next part of the buffer
//   return check_digit_recursive(buffer + 1, calibrated_digit);
// }
