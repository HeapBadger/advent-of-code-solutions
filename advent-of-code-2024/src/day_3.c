#include "array.h"
#include "aux.h"
#include "day_3.h"
#include "error.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_3.c
 * @brief Implementation of the Day 3 challenge.
 */

typedef struct
{
    Array *multiplicand;
    Array *multiplier;
    Array *conditional;
    bool   b_do_execute;
} PatternData;

/* Function Prototypes */
void         find_pattern(const char *input, PatternData *data);
bool         matches_pattern(const char *str, int *a, int *b);
PatternData *patterndata_initialization();
void         patterndata_destroy(PatternData *data);

int
day_3 (const char *filename, int result[2])
{
    FILE        *fptr              = NULL;
    char         line[BUFFER_SIZE] = { 0 };
    int          return_status     = ERROR_UNKNOWN;
    PatternData *data              = NULL;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_3");
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

    int sum_one = 0;
    int sum_two = 0;

    data = patterndata_initialization();

    if (NULL == data)
    {
        ERROR_LOG("Unable to initialize PatternData");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    while (NULL != fgets(line, sizeof(line), fptr))
    {
        find_pattern(line, data);
    }

    if ((data->multiplicand->idx != data->multiplier->idx)
        || (data->conditional->idx != data->multiplier->idx))
    {
        ERROR_LOG("Failed to correctly parse multipliers");
        goto EXIT;
    }

    for (int idx = 0; idx < data->multiplicand->idx; idx++)
    {
        sum_one += (*(int *)data->multiplicand->list[idx]
                    * *(int *)data->multiplier->list[idx]);
        sum_two += (*(int *)data->multiplicand->list[idx]
                    * *(int *)data->multiplier->list[idx]
                    * *(int *)data->conditional->list[idx]);
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

    patterndata_destroy(data);
    return return_status;
}

/**
 * @brief Parses an input string to find and process patterns of interest.
 *
 * @param input The input string to parse.
 * @param data Pointer to a PatternData structure that holds parsed data.
 */
void
find_pattern (const char *input, PatternData *data)
{
    if ((NULL == input) || (NULL == data))
    {
        ERROR_LOG("Invalid input to find_pattern");
        return;
    }

    const char *current_pos = input;

    while (NULL != current_pos)
    {
        const char *next_mul  = strstr(current_pos, "mul(");
        const char *next_do   = strstr(current_pos, "do()");
        const char *next_dont = strstr(current_pos, "don't()");

        // Find the nearest match among the patterns
        const char *next_match = next_mul;

        if ((NULL != next_do)
            && ((NULL == next_match) || (next_do < next_match)))
        {
            next_match = next_do;
        }

        if ((NULL != next_dont)
            && ((NULL == next_match) || (next_dont < next_match)))
        {
            next_match = next_dont;
        }

        if (NULL == next_match)
        {
            break; // No more matches found
        }

        // Process the found match
        if (0 == strncmp(next_match, "mul(", 4))
        {
            int a, b;
            if (matches_pattern(next_match, &a, &b))
            {
                if ((ERROR_SUCCESS
                     != array_add(data->multiplicand, &a, sizeof(int)))
                    || (ERROR_SUCCESS
                        != array_add(data->multiplier, &b, sizeof(int)))
                    || (ERROR_SUCCESS
                        != array_add(data->conditional,
                                     &data->b_do_execute,
                                     sizeof(int))))
                {
                    ERROR_LOG("Unable to add element to array");
                    break;
                }
            }
        }
        else if (0 == strncmp(next_match, "do(", 3))
        {
            data->b_do_execute = true; // enable mul()
        }
        else if (0 == strncmp(next_match, "don't(", 6))
        {
            data->b_do_execute = false; // disable mul()
        }

        // Move past the current match to continue searching
        current_pos = next_match + 1;
    }

    return;
}

/**
 * @brief Matches a string against the "mul(a, b)" pattern and extracts
 integers
 * a and b.
 *
 * @param str The input string to match.
 * @param a Pointer to store the first extracted integer.
 * @param b Pointer to store the second extracted integer.
 *
 * @return true if the string matches the pattern and integers are
 * successfully extracted, false otherwise.
 */
bool
matches_pattern (const char *str, int *a, int *b)
{
    bool return_status = false;

    if ((NULL == str) || (NULL == a) || (NULL == b))
    {
        goto EXIT;
    }

    if (0 != strncmp(str, "mul(", 4))
    {
        goto EXIT;
    }

    str += 4; // Skip "mul("
    char *end_ptr;

    // Extract the first integer
    *a = (int)strtol(str, &end_ptr, 10);

    if ((end_ptr == str) || (',' != *end_ptr))
    {
        goto EXIT; // No valid integer or missing ','
    }

    str = end_ptr + 1; // Move past ','

    // Extract the second integer
    *b = (int)strtol(str, &end_ptr, 10);

    if ((end_ptr == str) || (')' != *end_ptr))
    {
        goto EXIT; // No valid integer or missing ')'
    }

    return_status = true; // successfully extracted digits

EXIT:
    return return_status;
}

/**
 * @brief Initializes a PatternData structure and its associated arrays.
 *
 * @return Pointer to the initialized PatternData structure, or NULL on
 failure.
 */
PatternData *
patterndata_initialization ()
{
    PatternData *data = NULL;

    data = (PatternData *)calloc(1, sizeof(PatternData));

    if (NULL == data)
    {
        ERROR_LOG("Failed to allocate memory for PatternData");
        goto EXIT;
    }

    data->b_do_execute = true;
    data->conditional  = NULL;
    data->multiplicand = NULL;
    data->multiplier   = NULL;

    data->conditional  = array_initialization();
    data->multiplicand = array_initialization();
    data->multiplier   = array_initialization();

    if ((NULL == data->conditional) || (NULL == data->multiplicand)
        || (NULL == data->multiplier))
    {
        patterndata_destroy(data);
        data = NULL;
    }

EXIT:
    return data;
}

/**
 * @brief Frees memory associated with a PatternData structure and its
 arrays.
 *
 * @param data Pointer to the PatternData structure to destroy.
 */
void
patterndata_destroy (PatternData *data)
{
    if (NULL != data)
    {
        array_destroy(data->conditional);
        array_destroy(data->multiplicand);
        array_destroy(data->multiplier);
        free(data);
        data = NULL;
    }

    return;
}

/*** end of file ***/
