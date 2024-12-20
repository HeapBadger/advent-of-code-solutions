#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

/**
 * @file array.h
 * @brief Array utilities and definitions.
 *
 * This header file contains function declarations and macro definitions for
 * the array source file.
 */

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
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
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
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 *
 * @warning The caller must provide the correct size of the element being added,
 *          as the array can store any data type using void pointers.
 */
int array_add(Array *array, const void *ele, size_t ele_size);

/**
 * @brief Resets all elements in the array.
 *
 * This function resets all elements in the array by freeing any allocated
 * memory for each element and setting the pointers to `NULL`. The array itself
 * remains allocated with its current capacity.
 *
 * @param array Pointer to the array to be reset.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure:
 *         - ERROR_NULL_POINTER if the provided array is NULL.
 *
 * @warning This function does not resize the array or deallocate the array
 * structure itself. It only clears the contents of the array's elements.
 */
int array_reset(Array *array);

#endif // ARRAY_H
