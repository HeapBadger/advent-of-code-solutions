#ifndef AUX_H
#define AUX_H

/**
 * @file aux.h
 * @brief Auxiliary utilities and definitions for the project.
 *
 * This header file contains auxiliary function declarations and macro
 * definitions that are used across the project to provide common utilities and
 * helpers.
 */

#include <stdio.h>

#define ERROR_LOG(msg)                \
    do                                \
    {                                 \
        fprintf(stderr, "%s\n", msg); \
    } while (0)

#define DNE         -1
#define BUFFER_SIZE 256 ///< Maximum line size for file input.

/**
 * @brief Structure to hold an array.
 */
typedef struct
{
    int  max;  ///< Maximum size of the array.
    int  idx;  ///< Current index for inserting elements.
    int *list; ///< Array of integers.
} Array;

Array *array_initialization(void);
int    array_resize(Array *array);
void   array_destroy(Array *array);
int    array_add(Array *array, const int ele);

#endif // AUX_H
