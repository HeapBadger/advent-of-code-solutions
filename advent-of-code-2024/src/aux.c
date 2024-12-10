#include "aux.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file aux.c
 * @brief Supplementary functions to support challenges.
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
        return NULL;
    }

    array->idx  = 0;
    array->max  = INITIAL_SIZE;
    array->list = calloc(INITIAL_SIZE, sizeof(int));

    if (NULL == array->list)
    {
        ERROR_LOG("Failed to allocate memroy for Array");
        free(array);
        array = NULL;
        goto EXIT;
    }

    for (int idx = 0; idx < array->max; idx++)
    {
        array->list[idx] = DNE;
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

    int  new_size = array->max * 2;
    int *new_list = (int *)realloc(array->list, new_size * sizeof(int));

    if (NULL == new_list)
    {
        ERROR_LOG("Failed to resize arrays");
        goto EXIT;
    }

    for (int idx = array->max; idx < new_size; idx++)
    {
        new_list[idx] = DNE;
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
            free(array->list);
            array->list = NULL;
        }

        free(array);
        array = NULL;
    }
}

int
array_add (Array *array, const int ele)
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

    // Add the element
    array->list[array->idx] = ele;
    array->idx++;
    return_status = EXIT_SUCCESS;

EXIT:
    return return_status;
}

/*** end of file ***/