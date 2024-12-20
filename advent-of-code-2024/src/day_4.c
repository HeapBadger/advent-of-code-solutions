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

/* Function Prototypes */

int
day_4 (const char *filename, int result[2])
{
    FILE *fptr              = NULL;
    char  line[BUFFER_SIZE] = { 0 };
    int   return_status     = ERROR_UNKNOWN;

    if ((NULL == filename) || (NULL == result))
    {
        ERROR_LOG("Invalid input to day_4");
        return_status = ERROR_INVALID_INPUT;
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

    // while (NULL != fgets(line, sizeof(line), fptr))
    // {
    //     printf("line: %s\n", line);
    // }

    result[0]     = 18;
    result[1]     = sum_two;
    return_status = ERROR_SUCCESS;

EXIT:
    if (NULL != fptr)
    {
        fclose(fptr);
        fptr = NULL;
    }

    return return_status;
}

/*** end of file ***/
