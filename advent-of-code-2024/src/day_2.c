#include "array.h"
#include "aux.h"
#include "day_2.h"
#include "error.h"

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
static int extract_digits(const char *line, Array *record);
bool       b_is_stable(void **record, int size);
bool       b_is_stable_with_damper(void **record, int size);

int
day_2 (const char *filename, int result[2])
{
    FILE  *fptr              = NULL;
    char   line[BUFFER_SIZE] = { 0 };
    int    return_status     = ERROR_UNKNOWN;
    Array *record            = NULL;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_2");
        return_status = ERROR_INVALID_INPUT;
        goto EXIT;
    }

    fptr = fopen(filename, "r");

    if (NULL == fptr)
    {
        ERROR_LOG("Unable to open file");
        return_status = ERROR_FILE_NOT_FOUND;
        goto EXIT;
    }

    record = array_initialization(TYPE_INT);

    if (NULL == record)
    {
        ERROR_LOG("Unable to initialize array");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    while (NULL != fgets(line, sizeof(line), fptr))
    {
        // extract record from line
        if (ERROR_SUCCESS != extract_digits(line, record))
        {
            goto EXIT;
        }

        // add stability scores
        sum_one += b_is_stable(record->list, record->idx);
        sum_two += b_is_stable_with_damper(record->list, record->idx);

        // reset array for next record
        array_reset(record);
    }

    result[0]     = sum_one;
    result[1]     = sum_two;
    return_status = ERROR_SUCCESS;

EXIT:
    if (NULL != fptr)
    {
        fclose(fptr);
        fptr = NULL;
    }

    array_destroy(record);
    return return_status;
}

/**
 * @brief Extracts digits from a string and stores them in an Array.
 *
 * This function loops through each character in the line. If a digit is
 * found, it is stored in the Array. The Array's index is incremented
 * for each digit.
 *
 * @param line Pointer to a null-terminated string containing digits.
 * @param record Pointer to the Array structure where digits will be stored.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
extract_digits (const char *line, Array *record)
{
    int return_status = ERROR_UNKNOWN;

    if ((NULL == line) || (NULL == record))
    {
        ERROR_LOG("Invalid input to extract_digits");
        return_status = ERROR_INVALID_INPUT;
        goto EXIT;
    }

    while ('\0' != *line)
    {
        char *endline;
        int   ele = (int)strtol(line, &endline, 10);

        return_status = array_add(record, &ele);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Unable to add element to array");
            goto EXIT;
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
                return_status = ERROR_INVALID_INPUT;
                goto EXIT;
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

EXIT:
    return return_status;
}

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
b_is_stable (void **record, int size)
{
    bool stable = true;
    bool pos    = false;
    bool neg    = false;

    if ((NULL == record) || (1 >= size))
    {
        return stable;
    }

    for (int idx = 0; idx < size - 1; idx++)
    {
        int diff = *(int *)record[idx] - *(int *)record[idx + 1];

        // Check if the difference is within the valid range
        if (1 > abs(diff) || 3 < abs(diff))
        {
            stable = false;
            break;
        }

        // Track if the direction has changed
        if (0 < diff)
        {
            pos = true;
        }
        else
        {
            neg = true;
        }

        // Unstable if direction increases and decreases
        if ((true == pos) && (true == neg))
        {
            stable = false;
            break;
        }
    }

    return stable;
}

/**
 * @brief Checks the stability of a sequence of integers, allowing one
 * element to be removed.
 *
 * @param record Pointer to an array of integers representing the sequence.
 * @param size The size of the array.
 * @return `true` if the sequence is stable (either initially or after
 * removing one element), `false` otherwise.
 */
bool
b_is_stable_with_damper (void **record, int size)
{
    bool   stable     = false;
    void **mod_record = NULL;

    if ((NULL == record) || (1 >= size))
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
    mod_record = calloc(size - 1, sizeof(void *));

    if (NULL == mod_record)
    {
        ERROR_LOG("Failed to allocate memroy for mod_record");
        goto EXIT;
    }

    // Attempt to remove one element and check if the sequence becomes stable
    for (int idx = 0; idx < size; idx++)
    {
        for (int jdx = 0; jdx < size - 1; jdx++)
        {
            mod_record[jdx] = NULL;
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
    if (NULL != mod_record)
    {
        free(mod_record);
        mod_record = NULL;
    }

    return stable;
}

/*** end of file ***/
