#include "array.h"
#include "aux.h"
#include "day_1.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_1.c
 * @brief Implementation of the Day 1 challenge.
 */

/* Function Prototypes */
static int similarity_score(int num, void **array, int size);
static int extract_digits(const char *line, int digits[2]);
void       bubble_sort(Array *array);

int
day_1 (const char *filename, int result[2])
{
    int    return_status = ERROR_UNKNOWN;
    Array *array_one     = NULL;
    Array *array_two     = NULL;
    FILE  *fptr          = NULL;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_1");
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

    array_one = array_initialization(TYPE_INT);

    if (NULL == array_one)
    {
        ERROR_LOG("Unable to initialize array");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    array_two = array_initialization(TYPE_INT);

    if (NULL == array_two)
    {
        ERROR_LOG("Unable to initialize array");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    char line[BUFFER_SIZE] = { 0 };

    while (NULL != fgets(line, sizeof(line), fptr))
    {
        int digits[2] = { ERROR_ELEMENT_NOT_FOUND, ERROR_ELEMENT_NOT_FOUND };

        if (ERROR_SUCCESS == extract_digits(line, digits))
        {
            array_add(array_one, &digits[0]);
            array_add(array_two, &digits[1]);
        }
        else
        {
            ERROR_LOG("Unable to extract digits");
            goto EXIT;
        }
    }

    // Part 1: Compute sum of absolute differences
    bubble_sort(array_one);
    bubble_sort(array_two);

    int sum = 0;

    for (int idx = 0; idx < array_one->idx; idx++)
    {
        sum += abs(*(int *)array_one->list[idx] - *(int *)array_two->list[idx]);
    }

    result[0] = sum;

    // Part 2: Compute similarity scores
    sum = 0;

    for (int idx = 0; idx < array_one->idx; idx++)
    {
        sum += similarity_score(
            *(int *)array_one->list[idx], array_two->list, array_two->idx);
    }

    result[1]     = sum;
    return_status = ERROR_SUCCESS;

EXIT:
    if (NULL != fptr)
    {
        fclose(fptr);
        fptr = NULL;
    }

    array_destroy(array_one);
    array_destroy(array_two);
    return return_status;
}

/**
 * @brief Sorts an array of integers in ascending order using bubble sort.
 *
 * @param numbers Pointer to the array of integers.
 * @param size Number of elements in the array.
 */
void
bubble_sort (Array *array)
{
    if ((NULL == array) || (NULL == array->list) || (0 >= array->idx))
    {
        ERROR_LOG("Invalid array or size");
        return;
    }

    // Perform bubble sort on the array
    for (int i = array->idx - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (*(int *)array->list[j] > *(int *)array->list[j + 1])
            {
                void *tmp          = array->list[j];
                array->list[j]     = array->list[j + 1];
                array->list[j + 1] = tmp;
            }
        }
    }
}

/**
 * @brief Calculates a similarity score for a given integer.
 *
 * The similarity score is the product of the integer and its frequency
 * in the array. The array must be sorted and contain only valid integers.
 *
 * @param num The integer for which the similarity score is calculated.
 * @param array Pointer to a sorted void array filled with integers.
 * @param size The size of the array.
 * @return The similarity score if successful, or 0 on invalid input.
 */
static int
similarity_score (int num, void **array, int size)
{
    if ((0 > num) || (NULL == array) || (0 >= size))
    {
        return 0;
    }

    int count = 0;

    for (int idx = 0; idx < size; idx++)
    {
        if (ERROR_ELEMENT_NOT_FOUND == *(int *)array[idx])
        {
            continue;
        }
        if (*(int *)array[idx] > num)
        {
            break;
        }
        if (*(int *)array[idx] == num)
        {
            count++;
        }
    }
    return count * num;
}

/**
 * @brief Extracts two integers from a line of text.
 *
 * Parses a line of text for two integers and stores them in the `digits` array.
 *
 * @param line Input line of text.
 * @param digits Array to store the extracted integers (size 2).
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
extract_digits (const char *line, int digits[2])
{
    if ((NULL == line) || (NULL == digits))
    {
        ERROR_LOG("Invalid input to extract_digits");
        return ERROR_INVALID_INPUT;
    }

    if (sscanf(line, "%d %d", &digits[0], &digits[1]) != 2)
    {
        ERROR_LOG("Failed to parse integers");
        return ERROR_UNKNOWN;
    }

    return ERROR_SUCCESS;
}

/*** end of file ***/
