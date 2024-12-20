#include "aux.h"
#include "error.h"
#include "table.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @file table.c
 * @brief Table functions.
 *
 * This file contains functions handle all table functions. It assumes
 * the table contains arrays.
 */

Table *
table_initialization (ElementType ele_type, int num_rows)
{
    Table *table = NULL;

    if (0 >= num_rows)
    {
        ERROR_LOG(
            "Invalid input to table_initialization: Rows must be a positive "
            "number");
        goto EXIT;
    }

    table = calloc(1, sizeof(Table));

    if (NULL == table)
    {
        ERROR_LOG("Failed to allocate memory for Table");
        goto EXIT;
    }

    table->num_rows = num_rows;
    table->content  = calloc(table->num_rows, sizeof(Array *));

    if (NULL == table->content)
    {
        ERROR_LOG("Failed to allocate memory for Table->content");
        goto EXIT;
    }

    for (int idx = 0; idx < table->num_rows; idx++)
    {
        table->content[idx] = array_initialization(ele_type);

        if (NULL == table->content[idx])
        {
            table_destroy(table);
            table = NULL;
            goto EXIT;
        }
    }

EXIT:
    return table;
}

void
table_destroy (Table *table)
{
    if (NULL != table)
    {
        for (int idx = 0; idx < table->num_rows; idx++)
        {
            array_destroy(table->content[idx]);
        }

        free(table->content);
        table->content  = NULL;
        table->num_rows = 0;

        free(table);
        table = NULL;
    }

    return;
}

int
table_add_element (Table *table, int row, const void *ele)
{
    int return_status = ERROR_UNKNOWN;

    if ((NULL == table) || (NULL == ele))
    {
        ERROR_LOG("Invalid input to table_add_element: Table or ele are NULL");
        return_status = ERROR_NULL_POINTER;
    }
    else if ((0 > row) || (table->num_rows <= row))
    {
        ERROR_LOG(
            "Invalid input to table_add_element: Row index out of bounds");
        return_status = ERROR_INDEX_OUT_OF_BOUNDS;
    }
    else
    {
        return_status = array_add(table->content[row], ele);
    }

    return return_status;
}

int
table_reset_row (Table *table, int row)
{
    int return_status = ERROR_UNKNOWN;

    if (NULL == table)
    {
        ERROR_LOG("Invalid input to table_reset_row: Table is NULL");
        return_status = ERROR_NULL_POINTER;
    }
    else if ((0 > row) || (table->num_rows <= row))
    {
        ERROR_LOG("Invalid input to table_reset_row: Row index out of bounds");
        return_status = ERROR_INDEX_OUT_OF_BOUNDS;
    }
    else
    {
        return_status = array_reset(table->content[row]);
    }

    return return_status;
}

int
table_copy_row (Table *table, int src, int dst)
{
    int return_status = ERROR_UNKNOWN;

    if (NULL == table)
    {
        ERROR_LOG("Invalid input to table_copy_row: Table is NULL");
        return_status = ERROR_NULL_POINTER;
    }
    else if ((0 > src) || (table->num_rows <= src) || (0 > dst)
             || (table->num_rows <= dst))
    {
        ERROR_LOG("Invalid input to table_reset_row: Row index out of bounds");
        return_status = ERROR_INDEX_OUT_OF_BOUNDS;
    }
    else
    {
        return_status = array_copy(table->content[src], table->content[dst]);
    }

    return return_status;
}

void
table_print (Table *table)
{
    if (NULL == table)
    {
        ERROR_LOG("Invalid input to table_print: Table is NULL");
        return;
    }

    if ((NULL == table->content) || (0 >= table->num_rows))
    {
        ERROR_LOG("Invalid input to table_print: Table content is NULL");
        return;
    }

    printf("Table:\n");

    for (int idx = 0; idx < table->num_rows; idx++)
    {
        printf("\t");
        array_print(table->content[idx]);
    }

    printf("\n\n");
    return;
}

/*** end of file ***/
