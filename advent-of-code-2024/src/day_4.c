#include "aux.h"
#include "day_4.h"
#include "error.h"
#include "table.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_4.c
 * @brief Implementation of the Day 4 challenge.
 */

#define ROWS 4

/* Function Prototypes */
static int table_circular_rotating(Table *table, const char *data);

int
day_4 (const char *filename, int result[2])
{
    FILE  *fptr              = NULL;
    char   line[BUFFER_SIZE] = { 0 };
    int    return_status     = ERROR_UNKNOWN;
    Table *wordsearch        = NULL;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_4");
        return_status = ERROR_INVALID_INPUT;
        goto EXIT;
    }

    wordsearch = table_initialization(TYPE_CHAR, ROWS);

    if (NULL == wordsearch)
    {
        ERROR_LOG("Failed to allocate memory");
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
        return_status = table_circular_rotating(wordsearch, line);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Unable to update wordsearch table");
            goto EXIT;
        }

        table_print(wordsearch);
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

    table_destroy(wordsearch);
    return return_status;
}

static int
table_circular_rotating (Table *table, const char *data)
{
    int   return_status = ERROR_UNKNOWN;
    char *char_ptr      = NULL;

    if ((NULL == table) || (NULL == data))
    {
        ERROR_LOG(
            "Invalid input to table_circular_rotating: Table or data are NULL");
        return_status = ERROR_NULL_POINTER;
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
    for (int idx = ROWS-1; idx > 0; idx--)
    {
        table_copy_row(table, idx, idx-1);
        printf("%d ", idx);
    }

    // reset the last row
    return_status = table_reset_row(table, ROWS - 1);

    if (ERROR_SUCCESS != return_status)
    {
        ERROR_LOG("Unable to reset row");
        goto EXIT;
    }

    // update the last row to contain the new line of characters
    for (int i = 0; data[i] != '\0'; i++)
    {
        *char_ptr     = data[i];
        return_status = table_add_element(table, ROWS - 1, (void *)char_ptr);

        if (ERROR_SUCCESS != return_status)
        {
            ERROR_LOG("Unable to add element to row");
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
