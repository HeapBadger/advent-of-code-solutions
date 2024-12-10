#include "day_1.h"
#include "aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_1.c
 * @brief Implementation of the Day 1 challenge.
 */

/* Function Prototypes */
static int similarity_score(int num, const int *array, int size);
static int extract_digits(const char *line, int digits[2]);

int
day_1 (const char *filename, int result[2])
{
    int    return_status = EXIT_FAILURE;
    Array *array_one     = NULL;
    Array *array_two     = NULL;
    FILE  *fp            = NULL;

    if ((filename == NULL) || (result == NULL))
    {
        ERROR_LOG("Invalid input to day_1");
        goto EXIT;
    }

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        ERROR_LOG("Unable to open file");
        goto EXIT;
    }

    array_one = array_initialization();

    if (array_one == NULL)
    {
        ERROR_LOG("Unable to initialize array_one");
        goto EXIT;
    }

    array_two = array_initialization();

    if (array_two == NULL)
    {
        ERROR_LOG("Unable to initialize array_two");
        goto EXIT;
    }

    char line[BUFFER_SIZE] = { 0 };

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int digits[2] = { DNE, DNE };

        if (extract_digits(line, digits) == EXIT_SUCCESS)
        {
            array_add(array_one, digits[0]);
            array_add(array_two, digits[1]);
        }
    }

    fclose(fp);
    fp = NULL;

    // Part 1: Compute sum of absolute differences
    bubble_sort(array_one->list, array_one->idx);
    bubble_sort(array_two->list, array_two->idx);

    int sum = 0;

    for (int idx = 0; idx < array_one->idx; idx++)
    {
        sum += abs(array_one->list[idx] - array_two->list[idx]);
    }

    result[0] = sum;

    // Part 2: Compute similarity scores
    sum = 0;

    for (int idx = 0; idx < array_one->idx; idx++)
    {
        sum += similarity_score(
            array_one->list[idx], array_two->list, array_two->idx);
    }

    result[1] = sum;

EXIT:
    if (NULL != fp)
    {
        fclose(fp);
        fp = NULL;
    }

    array_destroy(array_one);
    array_destroy(array_two);
    return EXIT_SUCCESS;
}

/**
 * @brief Sorts an array of integers in ascending order using bubble sort.
 *
 * @param numbers Pointer to the array of integers.
 * @param size Number of elements in the array.
 */
void
bubble_sort (int numbers[], int size)
{
    if ((numbers == NULL) || (size <= 0))
    {
        ERROR_LOG("Invalid array or size");
        return;
    }

    for (int i = size - 1; i >= 0; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (numbers[j - 1] > numbers[j])
            {
                int tmp        = numbers[j - 1];
                numbers[j - 1] = numbers[j];
                numbers[j]     = tmp;
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
 * @param array Pointer to a sorted array of integers.
 * @param size The size of the array.
 * @return The similarity score if successful, or 0 on invalid input.
 */
static int
similarity_score (int num, const int *array, int size)
{
    if ((num < 0) || (array == NULL) || (size <= 0))
    {
        return 0;
    }

    int count = 0;
    for (int idx = 0; idx < size; idx++)
    {
        if (array[idx] == DNE)
        {
            continue;
        }
        if (array[idx] > num)
        {
            break;
        }
        if (array[idx] == num)
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
 * @return int EXIT_SUCCESS if successful, otherwise EXIT_FAILURE.
 */
static int
extract_digits (const char *line, int digits[2])
{
    if ((line == NULL) || (digits == NULL))
    {
        ERROR_LOG("Invalid input to extract_digits");
        return EXIT_FAILURE;
    }

    if (sscanf(line, "%d %d", &digits[0], &digits[1]) != 2)
    {
        ERROR_LOG("Failed to parse integers");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*** end of file ***/