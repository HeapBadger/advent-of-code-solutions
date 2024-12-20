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
 * @enum ElementType
 * @brief Defines the supported types for elements stored in the array.
 *
 * This enum is used to identify the type of the elements that are stored in
 * the `Array` structure. Each element in the array will have an associated
 * type that dictates how it should be handled.
 */
typedef enum
{
    TYPE_INT,    /**< Integer type */
    TYPE_FLOAT,  /**< Float type */
    TYPE_DOUBLE, /**< Double type */
    TYPE_CHAR,   /**< Character type */
} ElementType;

/**
 * @brief Structure to represent an array with dynamic size.
 *
 * The array is capable of holding any data type, with the actual data stored as
 * void pointers.
 */
typedef struct
{
    void **list; /**< Pointer to the array of elements.*/
    int    idx;  /**< Current index (number of elements stored in the array). */
    int    max;  /**< Maximum capacity of the array. */
    ElementType ele_type; /**< The type of the elements stored in the array. */
} Array;

/**
 * @brief Initializes an empty array.
 *
 * This function allocates memory for the array and sets up the initial
 * capacity. The elements are initialized to NULL to indicate empty slots.
 *
 * @param ele_type The type of elements stored in the array.
 * @return Pointer to the newly created array, or NULL on failure.
 */
Array *array_initialization(ElementType ele_type);

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
 * resized.
 *
 * @param array    Pointer to the array where the element is added.
 * @param ele      The element to be added.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int array_add(Array *array, const void *ele);

/**
 * @brief Resets all elements in the array.
 *
 * This function resets all elements in the array by freeing any allocated
 * memory for each element and setting the pointers to `NULL`. The array itself
 * remains allocated with its current capacity.
 *
 * @param array Pointer to the array to be reset.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 *
 * @warning This function does not resize the array or deallocate the array
 * structure itself. It only clears the contents of the array's elements.
 */
int array_reset(Array *array);

/**
 * @brief Copies the elements from one array to another.
 *
 * This function copies all elements from the source array (`src`) to the
 * destination array (`dst`). The destination array is reset before the copy
 * begins. The elements are copied one by one using the `array_add` function.
 *
 * @param src Pointer to the source array to be copied from.
 * @param dst Pointer to the destination array to be copied to.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int array_copy(Array *src, Array *dst);

/**
 * @brief Prints the contents of an array.
 *
 * @param array Pointer to the Array structure to print.
 *              Must not be NULL.
 */
void array_print(Array *array);

#endif // ARRAY_H
