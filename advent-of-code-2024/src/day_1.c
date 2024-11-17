#include "day_1.h"

#include <stdio.h>

/**
 * @file day_1.c
 * @brief Implementation of day 1 challenge.
 *
 * Provides the implementation of the functions declared in example.h.
 */

static int extract_calibration_value(const char *line);

/**
 * @brief See header file for details.
 */
int day_1(const char *filename) {
  printf("Hello world: %s\n", filename);
  return 0;
}

int extract_calibration_value(const char* line) {
    char first_digit = '\0';
    char last_digit = '\0';

    // Traverse the string and find the first and last digits
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i])) {
            if (first_digit == '\0') {
                first_digit = line[i];  // first digit
            }
            last_digit = line[i];  // last digit
        }
    }

    if (first_digit != '\0' && last_digit != '\0') {
        // Convert characters to integers and form the two-digit number
        return (first_digit - '0') * 10 + (last_digit - '0');
    }

    return 0;  // Return 0 if no valid calibration value is found
}
