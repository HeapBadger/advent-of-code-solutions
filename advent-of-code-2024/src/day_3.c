#include "day_3.h"
#include "aux.h"

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

// /* Function Prototypes */
void         find_pattern(const char *input, PatternData *data);
bool         matches_pattern(const char *str, int *a, int *b);
PatternData *patterndata_initialization();
void         patterndata_destroy();

int
day_3 (const char *filename, int result[2])
{
    FILE        *fp                = NULL;
    char         line[BUFFER_SIZE] = { 0 };
    int          return_status     = EXIT_FAILURE;
    PatternData *data              = NULL;

    if ((filename == NULL) || (result == NULL))
    {
        ERROR_LOG("Invalid input to day_3");
        goto EXIT;
    }

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        ERROR_LOG("Unable to open file");
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    data = patterndata_initialization();

    if (data == NULL)
    {
        ERROR_LOG("Unable to initialize PatternData");
        goto EXIT;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
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
    return_status = EXIT_SUCCESS;

EXIT:
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
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
    if ((input == NULL) || (data == NULL))
    {
        ERROR_LOG("Invalid input to find_pattern");
        return;
    }

    const char *current_pos = input;

    while (current_pos != NULL)
    {
        const char *next_mul  = strstr(current_pos, "mul(");
        const char *next_do   = strstr(current_pos, "do()");
        const char *next_dont = strstr(current_pos, "don't()");

        // Find the nearest match among the patterns
        const char *next_match = next_mul;

        if (next_do != NULL && (next_match == NULL || next_do < next_match))
        {
            next_match = next_do;
        }

        if (next_dont != NULL && (next_match == NULL || next_dont < next_match))
        {
            next_match = next_dont;
        }

        if (next_match == NULL)
        {
            break; // No more matches found
        }

        // Process the found match
        if (strncmp(next_match, "mul(", 4) == 0)
        {
            int a, b;
            if (matches_pattern(next_match, &a, &b))
            {
                // printf("(%d, %d) ", a, b);
                if ((array_add(data->multiplicand, &a, sizeof(int))
                     == EXIT_FAILURE)
                    || (array_add(data->multiplier, &b, sizeof(int))
                        == EXIT_FAILURE)
                    || (array_add(
                            data->conditional, &data->b_do_execute, sizeof(int))
                        == EXIT_FAILURE))
                {
                    ERROR_LOG("Unable to add element to array");
                    break;
                }
            }
        }
        else if (strncmp(next_match, "do(", 3) == 0)
        {
            data->b_do_execute = true; // enable mul()
        }
        else if (strncmp(next_match, "don't(", 6) == 0)
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
 successfully
 * extracted, false otherwise.
 */
bool
matches_pattern (const char *str, int *a, int *b)
{
    bool return_status = false;

    if (str == NULL || a == NULL || b == NULL)
    {
        goto EXIT;
    }

    if (strncmp(str, "mul(", 4) != 0)
    {
        goto EXIT;
    }

    str += 4; // Skip "mul("
    char *end_ptr;

    // Extract the first integer
    *a = (int)strtol(str, &end_ptr, 10);

    if (end_ptr == str || *end_ptr != ',')
    {
        goto EXIT; // No valid integer or missing ','
    }

    str = end_ptr + 1; // Move past ','

    // Extract the second integer
    *b = (int)strtol(str, &end_ptr, 10);

    if (end_ptr == str || *end_ptr != ')')
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

    if (data == NULL)
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

    if ((data->conditional == NULL) || (data->multiplicand == NULL)
        || (data->multiplier == NULL))
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
    if (data != NULL)
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
