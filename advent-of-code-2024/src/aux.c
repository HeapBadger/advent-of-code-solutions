#include "aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file aux.c
 * @brief Supplementary functions to support challenges.
 *
 * This file contains functions to initialize, resize, add elements, and destroy
 * an array. The array is dynamically allocated and can store any data type
 * using a `void *` pointer.
 */

#define INITIAL_SIZE 2

Array *
array_initialization (void)
{
    Array *array = calloc(1, sizeof(Array));

    if (NULL == array)
    {
        ERROR_LOG("Failed to allocate memory for Array");
        goto EXIT;
    }

    array->idx  = 0;
    array->max  = INITIAL_SIZE;
    array->list = calloc(
        INITIAL_SIZE,
        sizeof(void *)); /**< Allocating space for pointers to any data type. */

    if (NULL == array->list)
    {
        ERROR_LOG("Failed to allocate memory for Array");
        free(array);
        array = NULL;
        goto EXIT;
    }

    for (int idx = 0; idx < array->max; idx++)
    {
        array->list[idx] = NULL; /**< Initialize each element to NULL,
                                    indicating empty spots. */
    }

EXIT:
    return array;
}

int
array_resize (Array *array)
{
    int return_status = EXIT_FAILURE;

    if (NULL == array)
    {
        goto EXIT;
    }

    int    new_size = array->max * 2;
    void **new_list = (void **)realloc(
        array->list,
        new_size * sizeof(void *)); /**< Casting realloc to `void **`. */

    if (NULL == new_list)
    {
        ERROR_LOG("Failed to resize array");
        goto EXIT;
    }

    for (int idx = array->max; idx < new_size; idx++)
    {
        new_list[idx] = NULL; /**< Initialize new elements to NULL. */
    }

    array->max    = new_size;
    array->list   = new_list;
    return_status = EXIT_SUCCESS;

EXIT:
    return return_status;
}

void
array_destroy (Array *array)
{
    if (NULL != array)
    {
        if (NULL != array->list)
        {
            // Free each element (if needed, based on the type of data stored)
            for (int i = 0; i < array->idx; i++)
            {
                free(array->list[i]); /**< Free each dynamically allocated
                                         element. */
            }

            free(array->list);
            array->list = NULL;
        }

        free(array);
        array = NULL;
    }
}

int
array_add (Array *array, const void *ele, size_t ele_size)
{
    int return_status = EXIT_FAILURE;

    if (NULL == array)
    {
        ERROR_LOG("Invalid input to array_add: Array is NULL");
        goto EXIT;
    }

    // Check if resizing is needed
    if (array->idx >= array->max)
    {
        return_status = array_resize(array);
        if (EXIT_SUCCESS != return_status)
        {
            ERROR_LOG("Failed to resize array in array_add");
            goto EXIT;
        }
    }

    // Allocate memory for the new element and copy the data
    array->list[array->idx]
        = malloc(ele_size); /**< Allocate space for the element. */

    if (NULL == array->list[array->idx])
    {
        ERROR_LOG("Failed to allocate memory for new element in array_add");
        goto EXIT;
    }

    memcpy(array->list[array->idx],
           ele,
           ele_size); /**< Copy the data into the allocated space. */
    array->idx++;
    return_status = EXIT_SUCCESS;

EXIT:
    return return_status;
}

/*** end of file ***/
