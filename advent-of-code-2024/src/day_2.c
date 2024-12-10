#include "day_2.h"
#include "aux.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_2.c
 * @brief Implementation of the day_2 challenge.
 *
 * Provides functions for processing integer pairs from a file
 * and storing them in dynamically resizable arrays.
 */

/* Macros */
#define BUFFER_SIZE       (256) ///< Maximum line size for file input.
#define INITIAL_LIST_SIZE (10)  ///< Initial size of the arrays.
#define ELE_DNE           (-1)  ///< Marker for an empty array element.

/* Function Prototypes */
static int stability_calculator(const char *line);

/**
 * @brief Processes the file and extracts integer pairs.
 *
 * @param filename Path to the input file.
 * @param result Array to store the results.
 * @return int EXIT_SUCCESS on success, otherwise EXIT_FAILURE.
 */
int
day_2 (const char *filename, int result[2])
{
    FILE *fp                = NULL;
    char  line[BUFFER_SIZE] = { 0 };
    int   sum               = 0;

    if ((filename == NULL) || (result == NULL))
    {
        ERROR_LOG("Invalid input to day_2");
        return EXIT_FAILURE;
    }

    // Part One
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        ERROR_LOG("Unable to open file");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        sum += stability_calculator(line);
    }

    fclose(fp);
    result[1] = sum;

    // Part Two
    sum = 0;
    fp  = fopen(filename, "r");
    if (fp == NULL)
    {
        ERROR_LOG("Unable to open file");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        sum += stability_calculator(line);
    }

    fclose(fp);
    result[0] = sum;

    return EXIT_SUCCESS;
}

/**
 * @brief Calculates the stability score for a sequence of integers in a string.
 *
 * The stability score is determined based on the difference between consecutive
 * integers. If the absolute difference between any two integers exceeds 3,
 * the stability score is set to 0. Otherwise, the stability score is 1.
 *
 * Additionally the stability numbers in a line can only increase or decrease.
 *
 * @param line Pointer to a null-terminated string containing space-separated
 * integers. Must not be NULL.
 * @return Stability score (0 for unstable, 1 for stable).
 */
static int
stability_calculator (const char *line)
{
    if (line == NULL)
    {
        fprintf(stderr, "Error: Input line is NULL.\n");
        return 0; // Invalid input results in a stability score of 0
    }

    int  digits[2]       = { ELE_DNE, ELE_DNE };
    int  stability_score = 1;
    bool pos             = false;
    bool neg             = false;

    while (*line != '\0')
    {
        // Save the previous value
        digits[0] = digits[1];

        // Parse the next integer
        char *endline;
        digits[1] = (int)strtol(line, &endline, 10);

        // Check if no valid number was found
        if (line == endline)
        {
            if (isspace((unsigned char)*line))
            {
                line++; // Skip whitespace
                continue;
            }
            else
            {
                ERROR_LOG("invalid character in input");
                return 0;
            }
        }

        // Advance the line pointer to the next position
        line = endline;

        // Skip any trailing spaces
        while (isspace((unsigned char)*line))
        {
            line++;
        }

        if (digits[0] != ELE_DNE && digits[1] != ELE_DNE)
        {
            int diff = digits[0] - digits[1];

            if (diff < 0)
            {
                neg = true;
            }
            else if (diff > 0)
            {
                pos = true;
            }
            else
            {
                stability_score
                    = 0; // Adjacent numbers are equal, stability fails
                break;
            }

            // Check for instability conditions
            if ((pos && neg) || (abs(diff) > 3))
            {
                stability_score = 0;
                break;
            }
        }
    }

    return stability_score;
}
