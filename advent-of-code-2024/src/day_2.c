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
 */

/* Function Prototypes */
void extract_digits(const char *line, Array *record);
bool b_is_stable(int *record, int size);
bool b_is_stable_with_damper(int *record, int size);

int
day_2 (const char *filename, int result[2])
{
    FILE  *fp                = NULL;
    char   line[BUFFER_SIZE] = { 0 };
    int    return_status     = EXIT_FAILURE;
    Array *record            = NULL;

    if ((filename == NULL) || (result == NULL))
    {
        ERROR_LOG("Invalid input to day_2");
        goto EXIT;
    }

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        ERROR_LOG("Unable to open file");
        goto EXIT;
    }

    record = array_initialization();

    if (record == NULL)
    {
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // extract record from line
        extract_digits(line, record);

        // add stability scores
        sum_one += b_is_stable(record->list, record->idx); // part one
        sum_two
            += b_is_stable_with_damper(record->list, record->idx); // part two

        // reset array for next record
        record->idx = 0;
        memset(record->list, 0, record->max * sizeof(int));
    }

    result[0]     = sum_one;
    result[1]     = sum_two;
    return_status = EXIT_SUCCESS;

EXIT:
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

    array_destroy(record);
    return return_status;
}

/**
 * @brief Extracts digits from a string and stores them in an Array.
 *
 * This function loops through each character in the line. If a digit is found,
 * it is stored in the Array. The Array's index is incremented for each digit.
 *
 * @param line Pointer to a null-terminated string containing digits.
 * @param record Pointer to the Array structure where digits will be stored.
 */
void
extract_digits (const char *line, Array *record)
{
    if (line == NULL || record == NULL)
    {
        ERROR_LOG("Invalid input to extract_digits");
        return;
    }

    while (*line != '\0')
    {
        char *endline;
        int   ele = (int)strtol(line, &endline, 10);

        if (array_add(record, ele) == EXIT_FAILURE)
        {
            return;
        }

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
                ERROR_LOG("Invalid character in input");
                return;
            }
        }

        // Advance the line pointer to the next position
        line = endline;

        // Skip any trailing spaces
        while (isspace((unsigned char)*line))
        {
            line++;
        }
    }

    return;
}

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Checks the stability of a sequence of integers.
 *
 * The stability of a sequence is determined by the differences between
 * consecutive integers. A sequence is stable if the absolute difference
 * between any two consecutive integers is between 1 and 3 (inclusive),
 * and the sequence does not change direction (i.e., it either only increases
 * or only decreases).
 *
 * @param record Pointer to an array of integers representing the sequence.
 * @param size The size of the array.
 * @return `true` if the sequence is stable, `false` otherwise.
 */
bool
b_is_stable (int *record, int size)
{
    bool stable = true;
    bool pos    = false;
    bool neg    = false;

    if (record == NULL || size <= 1)
    {
        return stable;
    }

    for (int idx = 0; idx < size - 1; idx++)
    {
        int diff = record[idx] - record[idx + 1];

        // Check if the difference is within the valid range
        if (abs(diff) < 1 || abs(diff) > 3)
        {
            stable = false;
            break;
        }

        // Track if the direction has changed
        if (diff > 0)
        {
            pos = true;
        }
        else
        {
            neg = true;
        }

        // Unstable if direction increases and decreases
        if ((pos == true) && (neg == true))
        {
            stable = false;
            break;
        }
    }

    return stable;
}

/**
 * @brief Checks the stability of a sequence of integers, allowing one element
 * to be removed.
 *
 * This function first checks if the sequence is stable without modification. If
 * the sequence is not stable, it attempts to remove one element at a time and
 * checks if the resulting sequence becomes stable. A sequence is stable if the
 * absolute difference between any two consecutive integers is between 1 and 3
 * (inclusive), and the sequence does not change direction (i.e., it either only
 * increases or only decreases).
 *
 * @param record Pointer to an array of integers representing the sequence.
 * @param size The size of the array.
 * @return `true` if the sequence is stable (either initially or after removing
 * one element), `false` otherwise.
 */

bool
b_is_stable_with_damper (int *record, int size)
{
    bool stable     = false;
    int *mod_record = NULL;

    if (record == NULL || size <= 1)
    {
        goto EXIT;
    }

    // First, check if the sequence is stable without modification
    if (b_is_stable(record, size))
    {
        stable = true;
        goto EXIT;
    }

    // Next, attempt to remove an element and check stability
    mod_record = calloc(size - 1, sizeof(int));

    if (mod_record == NULL)
    {
        ERROR_LOG("Failed to allocate memroy for mod_record");
        goto EXIT;
    }

    // Attempt to remove one element and check if the sequence becomes stable
    for (int idx = 0; idx < size; idx++)
    {
        for (int jdx = 0; jdx < size - 1; jdx++)
        {
            mod_record[jdx] = DNE;
        }

        // Copy the elements, skipping the i-th element
        for (int jdx = 0, kdx = 0; jdx < size; jdx++)
        {
            if (jdx != idx)
            {
                mod_record[kdx++] = record[jdx];
            }
        }

        // Check if the new sequence is stable
        if (b_is_stable(mod_record, size - 1))
        {
            stable = true;
            goto EXIT;
        }
    }

EXIT:
    if (mod_record != NULL)
    {
        free(mod_record);
        mod_record = NULL;
    }

    return stable;
}

/*** end of file ***/