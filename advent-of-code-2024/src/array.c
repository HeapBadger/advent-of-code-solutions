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
array_initialization (ElementType ele_type)
{
    Array *array = calloc(1, sizeof(Array));

    if (NULL == array)
    {
        ERROR_LOG("Failed to allocate memory for Array");
        goto EXIT;
    }

    array->idx      = 0;
    array->ele_type = ele_type;
    array->max      = ARRAY_INITIAL_SIZE;
    array->list     = calloc(ARRAY_INITIAL_SIZE, sizeof(void *));

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
array_add (Array *array, const void *ele)
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

    size_t ele_size;

    switch (array->ele_type)
    {
        case TYPE_INT:
            ele_size = sizeof(int);
            break;
        case TYPE_FLOAT:
            ele_size = sizeof(float);
            break;
        case TYPE_DOUBLE:
            ele_size = sizeof(double);
            break;
        case TYPE_CHAR:
            ele_size = sizeof(char);
            break;
        default:
            ERROR_LOG("Unsupported element type");
            return_status = ERROR_INVALID_INPUT;
            goto EXIT;
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

int
array_copy (Array *src, Array *dst)
{
    int return_status = ERROR_NULL_POINTER;

    if ((NULL == src) || (NULL == dst))
    {
        ERROR_LOG("Cannot have null pointers as input");
        goto EXIT;
    }

    if ((NULL == src->list) || (NULL != dst->list))
    {
        ERROR_LOG("Cannot have null pointers as input lists");
        goto EXIT;
    }

    if (src->ele_type != dst->ele_type)
    {
        ERROR_LOG("Arrays must have matching data types");
        return_status = ERROR_INVALID_INPUT;
        goto EXIT;
    }

    // reset destination list
    return_status = array_reset(dst);

    if (ERROR_SUCCESS != return_status)
    {
        ERROR_LOG("Unable to reset destination array");
        goto EXIT;
    }

    // Copy each element from src to dst using array_add
    for (int idx = 0; idx < src->idx; idx++)
    {
        return_status = array_add(dst, src->list[idx]);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Failed to add element to destination array");
            break;
        }
    }

EXIT:
    return return_status;
}

void
array_print(Array *array)
{
    if (NULL == array)
    {
        ERROR_LOG("Invalid input to array_print: Array is NULL");
        return;
    }

    if (NULL == array->list)
    {
        ERROR_LOG("Invalid input to array_print: Array list is NULL");
        return;
    }

    for (int idx = 0; idx < array->idx; idx++)
    {
        if (NULL == array->list[idx])
        {
            printf("[NULL]");
        }
        else
        {
            switch (array->ele_type)
            {
                case TYPE_INT:
                    printf("%d", *(int *)array->list[idx]);
                    break;
                case TYPE_FLOAT:
                    printf("%f", *(float *)array->list[idx]);
                    break;
                case TYPE_DOUBLE:
                    printf("%lf", *(double *)array->list[idx]);
                    break;
                case TYPE_CHAR:
                    printf("%c", *(char *)array->list[idx]);
                    break;
                default:
                    printf("[UNKNOWN TYPE]");
                    break;
            }
        }

        if (idx < array->idx - 1)
        {
            printf(" ");
        }
    }

    printf("\n");
}

/*** end of file ***/
