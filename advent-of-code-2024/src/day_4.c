#include "aux.h"
#include "day_4.h"
#include "error.h"
#include "table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_4.c
 * @brief Implementation of the Day 4 challenge.
 */

/* Coordinate directions for 2D movement in a grid */
#define COORDS                                                        \
    {                                                                 \
        { 0, 1 }, { 0, -1 },     /* Forward, Backward */              \
            { 1, 0 }, { -1, 0 }, /* Down, Up */                       \
            { 1, 1 }, { 1, -1 }, /* Diagonal Down-Right, Down-Left */ \
            { -1, 1 },                                                \
        {                                                             \
            -1, -1                                                    \
        } /* Diagonal Up-Right, Up-Left */                            \
    }

/* Function Prototypes */
static int  part_one(Table *p_table, Array *p_found, const char *line);
static int  part_two(Table *p_table, Array *p_found, const char *p_line);
static int  table_rotate(Table *p_table, const char *p_data);
static int  table_search_frontback(Table *p_table, Array *p_found, const char *p_word);
static int  table_search_updown(Table *p_table, Array *p_found, const char *p_word);
static int  table_search_diagonal(Table *p_table, Array *p_found, const char *p_word);
static int  table_search_row(Table *p_table, Array *p_found, int row, const char *p_word, const int dir_range[2]);
static bool is_word_found(Table *table, const char *p_word, int row, int col, int dx, int dy);
static int  count_overlaps(Array *p_array);

int
day_4 (const char *filename, int result[2])
{
    FILE  *p_file            = NULL;
    Table *p_table_one       = NULL;
    Table *p_table_two       = NULL;
    Array *p_found           = NULL;
    char   line[BUFFER_SIZE] = { 0 };
    int    status            = ERROR_UNKNOWN;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_4: one or more inputs are NULL.");
        status = ERROR_NULL_POINTER;
        goto EXIT;
    }

    p_table_one = table_initialization(TYPE_CHAR, 4); // 4 row chunks for part 1
    p_table_two = table_initialization(TYPE_CHAR, 3); // 3 row chunks for part 2
    p_found     = array_initialization(
        TYPE_INT_PTR); // found coords for each table chunk

    if ((NULL == p_table_one) || (NULL == p_table_two) || (NULL == p_found))
    {
        ERROR_LOG("Failed initializations: unable to allocate memory");
        status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    p_file = fopen(filename, "r");

    if (NULL == p_file)
    {
        ERROR_LOG("Failed fopen: file not found");
        status = ERROR_FILE_NOT_FOUND;
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    while (NULL != fgets(line, sizeof(line), p_file))
    {
        status = part_one(p_table_one, p_found, line);

        if (ERROR_SUCCESS != status)
        {
            ERROR_LOG("Failed part_one");
            goto EXIT;
        }

        sum_one += p_found->idx;

        status = part_two(p_table_two, p_found, line);

        if (ERROR_SUCCESS != status)
        {
            ERROR_LOG("Failed part_two");
            goto EXIT;
        }

        sum_two += count_overlaps(p_found);
    }

    result[0] = sum_one;
    result[1] = sum_two;
    status    = ERROR_SUCCESS;

EXIT:
    if (NULL != p_file)
    {
        fclose(p_file);
        p_file = NULL;
    }

    table_destroy(p_table_one);
    table_destroy(p_table_two);
    array_destroy(p_found);
    return status;
}

/**
 * @brief Processes the first part of the challenge by rotating the table and searching for
 * all instances of the word "XMAS"
 *
 * @param p_table Pointer to the Table structure to be processed.
 * @param p_found Pointer to the Array structure that stores the coordinates of found words.
 * @param p_line  Pointer to the input line to be processed.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
part_one(Table *p_table, Array *p_found, const char *line)
{
    int status = table_rotate(p_table, line);

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed table_rotate: unable to update table");
        goto EXIT;
    }

    status = array_reset(p_found);

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed array_reset: unable to reset found array");
        goto EXIT;
    }

    status = table_search_frontback(p_table, p_found, "XMAS");

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed table_search_frontback: unable to search table for word");
        goto EXIT;
    }

    status = table_search_updown(p_table, p_found, "XMAS");

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed table_search_updown: unable to search table for word");
        goto EXIT;
    }

    status = table_search_diagonal(p_table, p_found, "XMAS");

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed table_search_diagonal: unable to search table for word");
        goto EXIT;
    }

EXIT:
    return status;
}

/**
 * @brief Processes the second part of the challenge by rotating the table and searching for
 * for diagonal instances of "MAS"
 *
 * @param p_table Pointer to the Table structure to be processed.
 * @param p_found Pointer to the Array structure that stores the coordinates of found words.
 * @param p_line  Pointer to the input line to be processed.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int 
part_two(Table *p_table, Array *p_found, const char *p_line)
{
    int status = table_rotate(p_table, p_line);

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed table_rotate: unable to update table");
        goto EXIT;
    }

    status = array_reset(p_found);

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed array_reset: unable to reset found array");
        goto EXIT;
    }

    status = table_search_diagonal(p_table, p_found, "MAS");

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed table_search_diagonal: unable to search table for word");
        goto EXIT;
    }

EXIT:
    return status;
}

/**
 * @brief Rotates a table by shifting rows upward and adding new data to the
 * last row.
 *
 * @param p_table Pointer to the table to update.
 * @param p_data  Pointer to the string data to add.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
table_rotate (Table *p_table, const char *p_data)
{
    int status = ERROR_UNKNOWN;

    if ((NULL == p_table) || (NULL == p_data))
    {
        ERROR_LOG(
            "Invalid input to table_rotate: one or more inputs are NULL.");
        status = ERROR_NULL_POINTER;
        goto EXIT;
    }

    // Shift rows upward
    for (int row = 0; row < p_table->num_rows - 1; row++)
    {
        status = table_copy_row(p_table, row + 1, row);

        if (ERROR_SUCCESS != status)
        {
            ERROR_LOG("Failed table_copy_row: unable to shift rows upward");
            goto EXIT;
        }
    }

    // Reset the last row
    status = table_reset_row(p_table, p_table->num_rows - 1);

    if (ERROR_SUCCESS != status)
    {
        ERROR_LOG("Failed table_reset_row: unable to clear the last row");
        goto EXIT;
    }

    // Add new data to the last row
    for (int idx = 0; p_data[idx] != '\0'; idx++)
    {
        status
            = table_add_element(p_table, p_table->num_rows - 1, &p_data[idx]);

        if (ERROR_SUCCESS != status)
        {
            ERROR_LOG(
                "Failed table_add_element: unable to add new row to table");
            goto EXIT;
        }
    }

EXIT:
    return status;
}

/**
 * @brief Searches the table for the word in the front and back direction. Only
 * searches the newest row to prevent repeats.
 *
 * @param p_table Pointer to the table to search.
 * @param p_found Array to store the found coordinates.
 * @param p_word Word to search for in the table.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
table_search_frontback (Table *p_table, Array *p_found, const char *p_word)
{
    if (p_table == NULL || p_word == NULL || p_found == NULL)
    {
        ERROR_LOG(
            "Invalid input to table_search_frontback: one or more inputs are "
            "NULL.");
        return ERROR_NULL_POINTER;
    }

    const int directions[] = { 0, 2 };
    return table_search_row(
        p_table, p_found, p_table->num_rows - 1, p_word, directions);
}

/**
 * @brief Searches the table for the word in the up and down direction.
 *
 * @param p_table Pointer to the table to search.
 * @param p_found Array to store the found coordinates.
 * @param p_word Word to search for in the table.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
table_search_updown (Table *p_table, Array *p_found, const char *p_word)
{
    int status = ERROR_UNKNOWN;

    if ((NULL == p_table) || (NULL == p_word) || (NULL == p_found))
    {
        ERROR_LOG(
            "Invalid input to table_search_updown: one or more inputs are "
            "NULL.");
        return ERROR_NULL_POINTER;
    }

    const int directions[] = { 2, 4 };

    for (int row = 0; row < p_table->num_rows; row++)
    {
        status = table_search_row(p_table, p_found, row, p_word, directions);

        if (ERROR_SUCCESS != status)
        {
            ERROR_LOG("Failed table_search_row: unable to search row for word");
            break;
        }
    }

    return status;
}

/**
 * @brief Searches the table for the word in diagonal directions.
 *
 * @param p_table Pointer to the table to search.
 * @param p_found Array to store the found coordinates.
 * @param p_word Word to search for in the table.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
table_search_diagonal (Table *p_table, Array *p_found, const char *p_word)
{
    int status = ERROR_UNKNOWN;

    if ((NULL == p_table) || (NULL == p_word) || (NULL == p_found))
    {
        ERROR_LOG(
            "Invalid input to table_search_diagonal: one or more inputs are "
            "NULL.");
        return ERROR_NULL_POINTER;
    }

    const int directions[] = { 4, 8 };

    for (int row = 0; row < p_table->num_rows; row++)
    {
        status = table_search_row(p_table, p_found, row, p_word, directions);

        if (ERROR_SUCCESS != status)
        {
            ERROR_LOG("Failed table_search_row: unable to search row for word");
            break;
        }
    }

    return status;
}

/**
 * @brief Searches the table for a word along a specified row and direction.
 *
 * @param p_table Pointer to the table to search.
 * @param p_found Array to store the found coordinates.
 * @param row Row to search in the table.
 * @param p_word Word to search for in the table.
 * @param dir_range Direction range for searching (e.g., forward/backward).
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
table_search_row (Table      *p_table,
                  Array      *p_found,
                  int         row,
                  const char *p_word,
                  const int   dir_range[2])
{
    int  coords[8][2] = COORDS;
    int *p_loc        = calloc(2, sizeof(int));

    if (NULL == p_loc)
    {
        ERROR_LOG("Failed calloc: unable to allocate memory");
        return ERROR_OUT_OF_MEMORY;
    }

    for (int col = 0; col < p_table->content[row]->idx; col++)
    {
        for (int dir_idx = dir_range[0]; dir_idx < dir_range[1]; dir_idx++)
        {
            if (is_word_found(p_table,
                              p_word,
                              row,
                              col,
                              coords[dir_idx][0],
                              coords[dir_idx][1]))
            {
                p_loc[0] = col + coords[dir_idx][1]; // x-axis
                p_loc[1] = row + coords[dir_idx][0]; // y-axis
                array_add(p_found, p_loc);
            }
        }
    }

    free(p_loc);
    p_loc = NULL;
    return ERROR_SUCCESS;
}

/**
 * @brief Checks if the word is found at the specified row and column.
 *
 * @param p_table Table to check.
 * @param p_word Word to check.
 * @param row Row index.
 * @param col Column index.
 * @param dx Horizontal movement (X direction).
 * @param dy Vertical movement (Y direction).
 *
 * @return true if the word is found, false otherwise.
 */
bool
is_word_found (
    Table *table, const char *p_word, int row, int col, int dx, int dy)
{
    if ((NULL == table) || (NULL == p_word))
    {
        ERROR_LOG(
            "Invalid input to is_word_found: one or more inputs are NULL");
        return false;
    }

    for (int idx = 0; idx < (int)strlen(p_word); idx++)
    {
        int new_row = row + idx * dx;
        int new_col = col + idx * dy;

        if ((0 > new_row) || (new_row >= table->num_rows) || (0 > new_col)
            || (new_col >= table->content[new_row]->idx))
        {
            return false; // Out of bounds
        }

        // Check if the character matches
        if (((char *)table->content[new_row]->list[new_col])[0] != p_word[idx])
        {
            return false; // Character does not match
        }
    }

    return true; // All characters matched
}

/**
 * @brief Counts overlaps in the found coordinates array.
 *
 * @param p_array Array containing found coordinates.
 *
 * @return The count of overlapping coordinates.
 */
static int
count_overlaps (Array *p_array)
{
    int word_count = 0;

    if (NULL == p_array)
    {
        ERROR_LOG("Invalid input to count_overlaps: input is NULL.");
        return word_count;
    }

    for (int idx = 0; idx < p_array->idx; idx++)
    {
        const int *coord_one = (const int *)p_array->list[idx];

        if (NULL == coord_one)
        {
            ERROR_LOG(
                "Failed type casting and dereferencing element: Null pointer "
                "detected in list");
            continue;
        }

        for (int jdx = idx + 1; jdx < p_array->idx; jdx++)
        {
            const int *coord_two = (const int *)p_array->list[jdx];

            if (NULL == coord_two)
            {
                ERROR_LOG(
                    "Failed type casting and dereferencing element: Null "
                    "pointer detected in list");
                continue;
            }

            if ((coord_one[0] == coord_two[0])
                && (coord_one[1] == coord_two[1]))
            {
                word_count++;
            }
        }
    }

    return word_count;
}

/*** end of file ***/
