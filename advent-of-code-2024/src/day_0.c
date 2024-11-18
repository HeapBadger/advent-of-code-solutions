#include "day_0.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file day_0.c
 * @brief Implementation of an example challenge.
 *
 * Provides the implementation of the functions declared in header file.
 */

#define BUFFER_SIZE 256

static int calibration_value(const char *line);

/**
 * @brief See header file for details.
 */
void day_0(const char *filename, int result[2]) {
  int sum;
  FILE *fp;
  char line[BUFFER_SIZE];

  ///// PART ONE /////
  sum = 0;
  fp = fopen(filename, "r");

  if (NULL == fp) {
    printf("[!] ERROR: unable to open file\n");
  }
  else {
    while (NULL != fgets(line, sizeof(line), fp)) {
      sum += calibration_value(line);
    }

    fclose(fp);
    result[0] = sum;
  }

  ///// PART TWO /////
  sum = 0;
  fp = fopen(filename, "r");

  if (NULL == fp) {
    printf("[!] ERROR: unable to open file\n");
  }
  else {
    while (NULL != fgets(line, sizeof(line), fp)) {
      sum += calibration_value(line);
    }

    fclose(fp);
    result[1] = sum;
  }

  ///// RETURN RESULT /////
  return sum;
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
static int calibration_value(const char *line) {
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
  return (calibrated_digit[0] - '0') * 10 + (calibrated_digit[1] - '0');;
}
