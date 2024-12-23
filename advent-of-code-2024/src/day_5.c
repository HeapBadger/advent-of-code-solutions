#include "array.h"
#include "aux.h"
#include "day_5.h"
#include "error.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_5.c
 * @brief Implementation of the Day 5 challenge.
 */

#define DIGITS_CAP 2

/* Function Prototypes */
Array *extract_digits(char *p_line, const char *p_delimiter);

int
day_5 (const char *filename, int result[2])
{
    FILE *p_file            = NULL;
    char  line[BUFFER_SIZE] = { 0 };
    int   status            = ERROR_UNKNOWN;
    Graph *p_graph = NULL;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_5: one or more inputs are NULL.");
        status = ERROR_NULL_POINTER;
        goto EXIT;
    }

    p_file = fopen(filename, "r");

    if (NULL == p_file)
    {
        ERROR_LOG("Failed fopen: file not found");
        status = ERROR_FILE_NOT_FOUND;
        goto EXIT;
    }

    p_graph = graph_initialization();

    if (NULL == p_graph)
    {
        ERROR_LOG("Failed graph_initialization: unable to allocate memory");
        status = ERROR_OUT_OF_MEMORY;
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    while (NULL != fgets(line, sizeof(line), p_file))
    {
        // Separator of rules and updates
        if (0 == strncmp(line, "\n", sizeof(line)))
        {
            break;
        }

        // Split the integers from the line
        Array *p_rules = extract_digits(line, "|");

        printf("(");
        array_print(p_rules);
        printf(")\n");

        if (DIGITS_CAP != p_rules->idx)
        {
            ERROR_LOG("Failed extract_digits: incorrect number of integers parsed");
        }
        else
        {
            // graph_add_edge(p_graph, *(int *)p_rules->list[0], *(int *)p_rules->list[1]); // should resize itself
        }

        array_destroy(p_rules);
    }

    // graph_sort(p_graph);
    result[0] = sum_one;
    result[1] = sum_two;
    status    = ERROR_SUCCESS;

EXIT:
    if (NULL != p_file)
    {
        fclose(p_file);
        p_file = NULL;
    }

    graph_destroy(p_graph);
    return status;
}

/**
 * @brief Extracts integers from a delimited string and stores them in an Array.
 *
 * @param p_line Pointer to a null-terminated string containing integers
 * separated by a delimiter.
 * @param p_delimiter Pointer to a null-terminated string containing a
 * delimiter.
 *
 * @return Pointer to an Array containing the extracted integers, or NULL on
 *         failure.
 *
 * @warning The caller is responsible for freeing the returned Array using
 *       `array_destroy`.
 */
Array *
extract_digits (char *p_line, const char *p_delimiter)
{
    Array *p_digits = NULL;

    if ((NULL == p_line) || (NULL == p_delimiter))
    {
        ERROR_LOG(
            "Invalid input to extract_digits: one or more inputs are NULL.");
        goto EXIT;
    }

    p_digits = array_initialization(TYPE_INT);

    if (NULL == p_digits)
    {
        ERROR_LOG("Failed array_initialization: unable to initialize array.");
        goto EXIT;
    }

    char *token = strtok(p_line, p_delimiter);

    while (NULL != token)
    {
        int value = atoi(token);

        if (array_add(p_digits, &value) != ERROR_SUCCESS)
        {
            ERROR_LOG("Failed array_add: unable to add an integer to array.");
            array_destroy(p_digits);
            p_digits = NULL;
            goto EXIT;
        }

        token = strtok(NULL, p_delimiter);
    }

EXIT:
    return p_digits;
}

/*** end of file ***/
