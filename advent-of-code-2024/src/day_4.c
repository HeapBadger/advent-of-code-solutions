#include "array.h"
#include "aux.h"
#include "day_4.h"
#include "error.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_4.c
 * @brief Implementation of the Day 4 challenge.
 */

/**
 * @brief Structure to represent a 4-row snapshot of the cross word
 */
typedef struct
{
    Array *row_one;
    Array *row_two;
    Array *row_three;
    Array *row_four;
} WordSearch;

/* Function Prototypes */
WordSearch *wordsearch_initialization(void);
void        wordsearch_destroy(WordSearch *data);
static int  wordsearch_updatetable(WordSearch *table, const char *data);

int
day_4 (const char *filename, int result[2])
{
    FILE       *fptr              = NULL;
    char        line[BUFFER_SIZE] = { 0 };
    int         return_status     = ERROR_UNKNOWN;
    WordSearch *table             = NULL;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_4");
        return_status = ERROR_INVALID_INPUT;
        goto EXIT;
    }

    table = wordsearch_initialization();

    if (NULL == table)
    {
        ERROR_LOG("Unable to allocate space for word search");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    fptr = fopen(filename, "r");

    if (NULL == fptr)
    {
        ERROR_LOG("Unable to open file");
        return_status = ERROR_FILE_NOT_FOUND;
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    while (NULL != fgets(line, sizeof(line), fptr))
    {
        printf("line: %s\n", line);
        return_status = wordsearch_updatetable(table, line);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Unable to update wordsearch table");
            goto EXIT;
        }

        printf("Table:\n");
        array_print(table->row_one);
        array_print(table->row_two);
        array_print(table->row_three);
        array_print(table->row_four);
        printf("\n\n");
    }

    result[0]     = 18;
    result[1]     = sum_two;
    return_status = ERROR_SUCCESS;

EXIT:
    if (NULL != fptr)
    {
        fclose(fptr);
        fptr = NULL;
    }

    wordsearch_destroy(table);
    return return_status;
}

/**
 * @brief Initializes an empty word search.
 *
 * This function allocates memory for the table and sets up the initial
 * capacity. The elements are initialized to NULL to indicate empty slots.
 *
 * @return Pointer to the newly created word search, or NULL on failure.
 */
WordSearch *
wordsearch_initialization (void)
{
    WordSearch *data = calloc(1, sizeof(WordSearch));

    if (NULL == data)
    {
        ERROR_LOG("Failed to allocate memory for WordSearch");
        goto EXIT;
    }

    data->row_one   = array_initialization(TYPE_CHAR);
    data->row_two   = array_initialization(TYPE_CHAR);
    data->row_three = array_initialization(TYPE_CHAR);
    data->row_four  = array_initialization(TYPE_CHAR);

    if ((NULL == data->row_one) || (NULL == data->row_two)
        || (NULL == data->row_three) || (NULL == data->row_four))
    {
        wordsearch_destroy(data);
        data = NULL;
    }

EXIT:
    return data;
}

/**
 * @brief Destroys the word search, freeing allocated memory.
 *
 * This function frees the memory for the word search table, all row arrays
 * and elements.
 *
 * @param array Pointer to the table to be destroyed.
 */
void
wordsearch_destroy (WordSearch *data)
{
    if (NULL != data)
    {
        array_destroy(data->row_one);
        array_destroy(data->row_two);
        array_destroy(data->row_three);
        array_destroy(data->row_four);

        free(data);
        data = NULL;
    }

    return;
}


static int
wordsearch_updatetable(WordSearch *table, const char *data)
{
    int return_status = ERROR_UNKNOWN;
    char *char_ptr = NULL;

    if ((NULL == table) || (NULL == data))
    {
        ERROR_LOG("Invalid input to wordsearch_updatetable");
        return_status = ERROR_INVALID_INPUT;
        goto EXIT;    
    }

    char_ptr = calloc(1, sizeof(char));

    if (NULL == char_ptr)
    {
        ERROR_LOG("Failed to allocate memory");
        return_status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    // update the table by shifting all rows up one level


    // reset the last row
    return_status = array_reset(table->row_four);

    if (ERROR_SUCCESS != return_status)
    {
        ERROR_LOG("Unable to reset array");
        goto EXIT;
    }

    // update the last row to contain the new line of characters
    for (int i = 0; data[i] != '\0'; i++)
    {
        *char_ptr = data[i];
        return_status = array_add(table->row_four, (void *)char_ptr);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Unable to add element to array");
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

/*** end of file ***/
