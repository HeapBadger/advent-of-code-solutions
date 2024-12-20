#include "array.h"
#include "aux.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file array.c
 * @brief Arrray functions.
 *
 * This file contains functions handle all array functions. The array
 * is dynamically allocated and can store any data type using a `void *`
 * pointer.
 */

#define ARRAY_INITIAL_SIZE 10

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
    array->max  = ARRAY_INITIAL_SIZE;
    array->list = calloc(ARRAY_INITIAL_SIZE, sizeof(void *));

    if (NULL == array->list)
    {
        ERROR_LOG("Failed to allocate memory for Array");
        free(array);
        array = NULL;
        goto EXIT;
    }

    for (int idx = 0; idx < array->max; idx++)
    {
        array->list[idx] = NULL;
    }

EXIT:
    return array;
}

int
array_resize (Array *array)
{
    int return_status = ERROR_NULL_POINTER;

    if (NULL == array)
    {
        goto EXIT;
    }

    int    new_size = array->max * 2;
    void **new_list = (void **)realloc(array->list, new_size * sizeof(void *));

    if (NULL == new_list)
    {
        ERROR_LOG("Failed to resize array");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    // Initialize new elements to NULL
    for (int idx = array->max; idx < new_size; idx++)
    {
        new_list[idx] = NULL;
    }

    array->max    = new_size;
    array->list   = new_list;
    return_status = ERROR_SUCCESS;

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
            for (int i = 0; i < array->idx; i++)
            {
                free(array->list[i]);
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
    int return_status = ERROR_NULL_POINTER;

    if (NULL == array)
    {
        ERROR_LOG("Invalid input to array_add: Array is NULL");
        goto EXIT;
    }

    // Check if resizing is needed
    if (array->idx >= array->max)
    {
        return_status = array_resize(array);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Failed to resize array in array_add");
            goto EXIT;
        }
    }

    // Allocate memory for the new element and copy the data
    array->list[array->idx] = calloc(1, ele_size);

    if (NULL == array->list[array->idx])
    {
        ERROR_LOG("Failed to allocate memory for new element in array_add");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    // Copy data into the allocated space
    memcpy(array->list[array->idx], ele, ele_size);
    array->idx++;
    return_status = ERROR_SUCCESS;

EXIT:
    return return_status;
}

int
array_reset (Array *array)
{
    int return_status = ERROR_NULL_POINTER;

    if (NULL == array)
    {
        ERROR_LOG("Invalid input to array_reset: Array is NULL");
        goto EXIT;
    }

    if (NULL != array->list)
    {
        for (int i = 0; i < array->idx; i++)
        {
            free(array->list[i]);
            array->list[i] = NULL;
        }

        array->idx    = 0;
        return_status = ERROR_SUCCESS;
    }
    else
    {
        return_status = ERROR_NULL_POINTER;
    }

EXIT:
    return return_status;
}

/*** end of file ***/
