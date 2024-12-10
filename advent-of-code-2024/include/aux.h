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
 *
 * The array is capable of holding any data type, with the actual data stored as
 * void pointers.
 */
typedef struct
{
    int    max;  ///< Maximum capacity of the array.
    int    idx;  ///< Current index for inserting elements.
    void **list; ///< Pointer to the array of void pointers (for any data type).
} Array;

/**
 * @brief Initializes an empty array.
 *
 * This function allocates memory for the array and sets up the initial
 * capacity. The elements are initialized to NULL to indicate empty slots.
 *
 * @return Pointer to the newly created array, or NULL on failure.
 */
Array *array_initialization(void);

/**
 * @brief Resizes the array to a larger capacity.
 *
 * This function reallocates memory for the array to double its size.
 * New elements are initialized to NULL.
 *
 * @param array Pointer to the array to be resized.
 * @return 0 on success, or a negative value on failure.
 */
int array_resize(Array *array);

/**
 * @brief Destroys the array, freeing allocated memory.
 *
 * This function frees the memory for both the array and its elements.
 * Each element is assumed to have been dynamically allocated and will be freed.
 *
 * @param array Pointer to the array to be destroyed.
 */
void array_destroy(Array *array);

/**
 * @brief Adds an element to the array.
 *
 * This function adds an element to the array. If the array is full, it is
 * resized. The element is copied into the array, with the caller providing the
 * correct size of the element.
 *
 * @param array    Pointer to the array where the element is added.
 * @param ele      The element to be added.
 * @param ele_size The size of the element being added.
 * @return 0 on success, or a negative value on failure.
 *
 * @warning The caller must provide the correct size of the element being added,
 *          as the array can store any data type using void pointers.
 */
int array_add(Array *array, const void *ele, size_t ele_size);

#endif // AUX_H
