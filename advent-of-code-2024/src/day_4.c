#include "aux.h"
#include "day_4.h"
#include "error.h"
#include "table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file day_4.c
 * @brief Implementation of the Day 4 challenge.
 */

#define ROWS     4
#define WORD     "XMAS"
#define WORD_LEN 4

/* Function Prototypes */
static int table_rotate(Table *table, const char *data);
int        table_search_word(Table *table, const char *word);
bool       direction_search_word(
          Table *table, const char *word, int row, int col, int dx, int dy);

int
day_4 (const char *filename, int result[2])
{
    FILE  *fptr              = NULL;
    char   line[BUFFER_SIZE] = { 0 };
    int    return_status     = ERROR_UNKNOWN;
    Table *table             = NULL;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_4: filename or result are NULL");
        return_status = ERROR_INVALID_INPUT;
        goto EXIT;
    }

    table = table_initialization(TYPE_CHAR, ROWS);

    if (NULL == table)
    {
        ERROR_LOG("Failed table_initialization: unable to allocate memory");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    fptr = fopen(filename, "r");

    if (NULL == fptr)
    {
        ERROR_LOG("Failed fopen: file not found");
        return_status = ERROR_FILE_NOT_FOUND;
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    while (NULL != fgets(line, sizeof(line), fptr))
    {
        return_status = table_rotate(table, line);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Failed table_rotate: unable to update table");
            goto EXIT;
        }

        sum_one += table_search_word(table, WORD);
    }

    result[0]     = sum_one;
    result[1]     = sum_two;
    return_status = ERROR_SUCCESS;

EXIT:
    if (NULL != fptr)
    {
        fclose(fptr);
        fptr = NULL;
    }

    table_destroy(table);
    return return_status;
}

/**
 * @brief Rotates the rows of a table in a circular manner and adds new data to
 * the last row.
 *
 * This function shifts all rows in the table up by one position. The last row
 * is reset and updated to contain the provided data, with each character of the
 * data being added individually as elements in the row.
 *
 * @param table Pointer to the Table structure to be updated.
 * @param data  Null-terminated string containing the data to be added to the
 * last row.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
static int
table_rotate (Table *table, const char *data)
{
    int   return_status = ERROR_UNKNOWN;
    char *char_ptr      = NULL;

    if ((NULL == table) || (NULL == data))
    {
        ERROR_LOG("Invalid input to table_rotate: table or data are NULL");
        return_status = ERROR_NULL_POINTER;
        goto EXIT;
    }

    char_ptr = calloc(1, sizeof(char));

    if (NULL == char_ptr)
    {
        ERROR_LOG("Failed calloc: unable to allocate memory");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    // Update the table by shifting all rows up one level
    for (int idx = 0; idx < table->num_rows - 1; idx++)
    {
        table_copy_row(table, idx + 1, idx);
    }

    // Reset the last row
    return_status = table_reset_row(table, table->num_rows - 1);

    if (ERROR_SUCCESS != return_status)
    {
        ERROR_LOG("Failed table_reset_row: unable to reset row");
        goto EXIT;
    }

    // Update the last row to contain the new line of characters
    for (int i = 0; data[i] != '\0'; i++)
    {
        *char_ptr = data[i];
        return_status
            = table_add_element(table, table->num_rows - 1, (void *)char_ptr);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Failed table_add_element: unable to add element to row");
            goto EXIT;
        }
    }

EXIT:
    if (NULL != char_ptr)
    {
        free(char_ptr);
        char_ptr = NULL;
    }

    return return_status;
}

/**
 * @brief Searches for a given word in a specific direction from a starting
 * position in the table.
 *
 * This function checks if the given word matches starting from the specified
 * position (row, col) in the table and in the specified direction (dx, dy).
 *
 * @param table Pointer to the Table structure.
 * @param word  Pointer to the null-terminated string representing the word to
 * search for.
 * @param row   Starting row index for the search.
 * @param col   Starting column index for the search.
 * @param dx    Row direction increment for the search.
 * @param dy    Column direction increment for the search.
 *
 * @return `true` if the word is found in the specified direction, otherwise
 * `false`.
 */
bool
direction_search_word (
    Table *table, const char *word, int row, int col, int dx, int dy)
{
    if ((NULL == table) || (NULL == word))
    {
        ERROR_LOG("Invalid input to direction_search_word: table or word are NULL");
        return false;
    }

    int word_len = WORD_LEN;

    for (int i = 0; i < word_len; i++)
    {
        int new_row = row + i * dx;
        int new_col = col + i * dy;

        // Check boundary conditions
        if (new_row < 0 || new_row >= table->num_rows || new_col < 0
            || new_col >= table->content[new_row]->idx)
        {
            return false; // Out of bounds
        }

        // Check if the character matches
        if (((char *)table->content[new_row]->list[new_col])[0] != word[i])
        {
            return false; // Character does not match
        }
    }

    return true; // All characters matched
}

/**
 * @brief Searches for occurrences of a word in the table across specified
 * directions.
 *
 * This function counts all occurrences of the given word in the table:
 * - It checks only forward and backward directions on the newest row.
 * - It checks up, down, and diagonal directions across all rows of the table.
 *
 * @param table Pointer to the Table structure.
 * @param word  Pointer to the null-terminated string representing the word to
 * search for.
 *
 * @return The total number of occurrences of the word in the table.
 */
int
table_search_word (Table *table, const char *word)
{
    int word_count = 0;

    if ((NULL == table) || (NULL == word))
    {
        ERROR_LOG("Invalid input to table_search_word: table or word are NULL");
        return word_count;
    }

    // Define direction sets
    int all_directions[8][2] = {
        { 0, 1 },  { 0, -1 }, // Forward, Backward
        { 1, 0 },  { -1, 0 }, // Down, Up
        { 1, 1 },  { 1, -1 }, // Diagonal Down-Right, Down-Left
        { -1, 1 }, { -1, -1 } // Diagonal Up-Right, Up-Left
    };

    int forward_backward[2][2] = {
        { 0, 1 }, { 0, -1 } // Forward, Backward
    };

    // Check the newest row for forward/backward directions
    int row = table->num_rows - 1;

    for (int col = 0; col < table->content[row]->idx; col++)
    {
        for (int dir = 0; dir < 2; dir++) // Only forward and backward
        {
            if (direction_search_word(table, word, row, col,
                                      forward_backward[dir][0],
                                      forward_backward[dir][1]))
            {
                word_count++;
            }
        }
    }

    // Check all rows for up/down and diagonal directions
    for (row = 0; row < table->num_rows; row++)
    {
        for (int col = 0; col < table->content[row]->idx; col++)
        {
            for (int dir = 2; dir < 8; dir++) // Skip forward/backward
            {
                if (direction_search_word(table, word, row, col,
                                          all_directions[dir][0],
                                          all_directions[dir][1]))
                {
                    word_count++;
                }
            }
        }
    }

    return word_count;
}

/*** end of file ***/
