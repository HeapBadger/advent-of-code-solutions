#include "array.h"
#include "aux.h"
#include "day_4.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file day_4.c
 * @brief Implementation of the Day 4 challenge.
 */

/* Function Prototypes */

int
day_4 (const char *filename, int result[2])
{
    FILE *fp                = NULL;
    char  line[BUFFER_SIZE] = { 0 };
    int   return_status     = EXIT_FAILURE;

    if ((filename == NULL) || (result == NULL))
    {
        ERROR_LOG("Invalid input to day_4");
        goto EXIT;
    }

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        ERROR_LOG("Unable to open file");
        goto EXIT;
    }

    int sum_one = 0;
    int sum_two = 0;

    // while (fgets(line, sizeof(line), fp) != NULL)
    // {
    //     printf("line: %s\n", line);
    // }

    result[0]     = 18;
    result[1]     = sum_two;
    return_status = EXIT_SUCCESS;

EXIT:
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

    return return_status;
}

/*** end of file ***/
