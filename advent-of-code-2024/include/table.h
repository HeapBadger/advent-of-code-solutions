#ifndef TABLE_H
#define TABLE_H

#include "array.h"

/**
 * @file table.h
 * @brief Table utilities and definitions.
 *
 * This header file contains function declarations and macro definitions for
 * the table source file.
 */

/**
 * @brief Structure to represent an table.
 *
 * The table contains rows of matching data type.
 */
typedef struct
{
    Array **content;  /**< Contains the arrays within the table. */
    int     num_rows; /**< Number of rows within the table. */
} Table;

/**
 * @brief Initializes an empty table.
 *
 * This function allocates memory for the table and sets up num_rows
 * of arrays.
 *
 * @param ele_type The type of elements stored in the array.
 * @param num_rows The number of rows within the table.
 * @return Pointer to the newly created table, or NULL on failure.
 */
Table *table_initialization(ElementType ele_type, int num_rows);

/**
 * @brief Destroys the table, freeing allocated memory.
 *
 * This function frees the memory for both the table and its content.
 *
 * @param table Pointer to the table to be destroyed.
 */
void table_destroy(Table *table);

/**
 * @brief Adds an element to the table.
 *
 * This function adds an element to a row within the table.
 *
 * @param table Pointer to the table.
 * @param row   Row number to indicate array where the element is added.
 * @param ele   The element to be added.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int table_add_element(Table *table, int row, const void *ele);

/**
 * @brief Resets all elements within a specific row within the table.
 *
 * This function resets all elements in the row by freeing any allocated
 * memory for each element and setting the pointers to `NULL`. The row itself
 * remains allocated with its current capacity.
 *
 * @param table Pointer to the table.
 * @param row   Row number to indate array to be reset.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 *
 * @warning This function does not resize the row or deallocate the row
 * structure itself. It only clears the contents of the row's elements.
 */
int table_reset_row(Table *table, int row);

/**
 * @brief Copies the elements from one row to another.
 *
 * This function copies all elements from the source row to the destination
 * row (`dst`). The destination row is reset before the copy begins.
 *
 * @param table Pointer to the table.
 * @param src Row number for the source row.
 * @param dst Row number for the destination row.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int table_copy_row(Table *table, int src, int dst);

/**
 * @brief Prints the contents of a table.
 *
 * @param table Pointer to the Table structure to print.
 *              Must not be NULL.
 */
void table_print(Table *table);

#endif // TABLE_H
