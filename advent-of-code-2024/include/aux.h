#ifndef AUX_H
#define AUX_H

#include <stdio.h>

/**
 * @file aux.h
 * @brief Auxiliary utilities and definitions for the project.
 *
 * This header file contains function declarations and macro definitions for
 * common utilities and helpers used across the project.
 */

// Error logging macro to print messages to stderr.
#define ERROR_LOG(msg)                \
    do                                \
    {                                 \
        fprintf(stderr, "%s\n", msg); \
    } while (0)

// Definitions for special values.
#define DNE         -1   ///< Indicates "Does Not Exist" or invalid.
#define BUFFER_SIZE 4096 ///< Maximum size for file input lines.

/**
 * @brief Structure to represent an array with dynamic size.
 */
typedef struct
{
    int  max;  ///< Maximum capacity of the array.
    int  idx;  ///< Current index for inserting elements.
    int *list; ///< Pointer to the array of integers.
} Array;

/**
 * @brief Initializes an empty array.
 *
 * @return Pointer to the newly created array, or NULL on failure.
 */
Array *array_initialization(void);

/**
 * @brief Resizes the array to a larger capacity.
 *
 * @param array Pointer to the array to be resized.
 * @return 0 on success, or a negative value on failure.
 */
int array_resize(Array *array);

/**
 * @brief Destroys the array, freeing allocated memory.
 *
 * @param array Pointer to the array to be destroyed.
 */
void array_destroy(Array *array);

/**
 * @brief Adds an element to the array.
 *
 * @param array Pointer to the array where the element is added.
 * @param ele   The element to be added.
 * @return 0 on success, or a negative value on failure.
 */
int array_add(Array *array, const int ele);

#endif // AUX_H
