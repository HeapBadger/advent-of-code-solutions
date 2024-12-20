#include "array.h"
#include "aux.h"
#include "day_1.h"
#include "day_2.h"
#include "day_3.h"
#include "day_4.h"
#include "error.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * @file main.c
 * @brief Entry point for running Advent of Code challenges.
 *
 * Supports running all challenges or a specific day's challenge using
 * command-line arguments.
 */

#define USAGE_GUIDE "Usage: ./adventofcode [<day_1|day_2|...>]"
#define ARGS_COUNT  2

/**
 * @brief Structure to map day names to their respective functions.
 */
typedef struct
{
    const char *day_name;
    int (*day_function)(const char *file_path, int result[]);
    int day_number;
} DayChallenge;

/**
 * @brief Runs a specific day's challenge.
 *
 * This function takes a `DayChallenge` structure, which includes the day name
 * and its associated function pointer, and executes the corresponding challenge
 * function. It checks for the existence of `example_<day_number>.txt` and
 * `actual_<day_number>.txt` files in the `data/` directory and runs the
 * function with these files if they exist.
 *
 * @param challenge A `DayChallenge` structure containing the day name,
 * function, and day number.
 *
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int
run_day (DayChallenge challenge)
{
    int return_status;
    printf("\nRunning %s challenge...\n", challenge.day_name);

    char example_file[BUFFER_SIZE];
    char actual_file[BUFFER_SIZE];
    int  result_array[2] = { 0, 0 };

    // construct file paths using the day number
    snprintf(example_file,
             sizeof(example_file),
             "data/example_%d.txt",
             challenge.day_number);
    snprintf(actual_file,
             sizeof(actual_file),
             "data/actual_%d.txt",
             challenge.day_number);

    // check and run the example file if it exists
    if (0 == access(example_file, F_OK))
    {
        printf("\tFound example file: %s. Running...\n", example_file);
        return_status = challenge.day_function(example_file, result_array);
    }
    else
    {
        ERROR_LOG("example file not found");
        return_status = ERROR_FILE_NOT_FOUND;
    }

    if (ERROR_SUCCESS == return_status)
    {
        printf("\tPart One: %d\n\tPart Two: %d\n\n",
               result_array[0],
               result_array[1]);
    }

    // check and run the actual file if it exists
    result_array[0] = 0;
    result_array[1] = 0;

    if (0 == access(actual_file, F_OK))
    {
        printf("\tFound actual file: %s. Running...\n", actual_file);
        return_status = challenge.day_function(actual_file, result_array);
    }
    else
    {
        ERROR_LOG("actual file not found");
        return_status = ERROR_FILE_NOT_FOUND;
    }

    if (ERROR_SUCCESS == return_status)
    {
        printf("\tPart One: %d\n\tPart Two: %d\n\n",
               result_array[0],
               result_array[1]);
    }

    return return_status;
}

/**
 * @brief Entry point of the program.
 *
 * This function handles the logic for running either all challenges or a
 * specific day's challenge based on the command-line argument. It accepts the
 * following arguments:
 * - If no arguments are passed, it runs all the challenges.
 * - If a valid day name (e.g., "day_1") is passed, it runs the corresponding
 * day's challenge.
 *
 * @param argc Argument count, representing the number of command-line
 * arguments.
 * @param argv Argument vector, an array of strings containing the command-line
 * arguments.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int
main (int argc, char *argv[])
{
    int return_status = ERROR_SUCCESS;

    // array of all available challenges
    DayChallenge challenges[] = {
        { "day_1", day_1, 1 },
        { "day_2", day_2, 2 },
        { "day_3", day_3, 3 },
        { "day_4", day_4, 4 },
        // add additional days here as needed
    };

    size_t challenge_count = sizeof(challenges) / sizeof(challenges[0]);

    // run all challenges
    if (ARGS_COUNT > argc)
    {
        printf("Running all Advent of Code challenges...\n");

        for (size_t idx = 0; idx < challenge_count; idx++)
        {
            return_status = run_day(challenges[idx]);

            if (ERROR_SUCCESS != return_status)
            {
                break;
            }
        }
    }

    // print usage guide (too many arguments handed)
    else if (ARGS_COUNT < argc)
    {
        ERROR_LOG("invalid argument");
        printf("%s\n", USAGE_GUIDE);
        return_status = ERROR_INVALID_INPUT;
    }

    // run a specific challenge if it exists
    else
    {
        const char *requested_chal = argv[1];
        bool        found          = false;

        for (size_t idx = 0; idx < challenge_count; idx++)
        {
            if (0 == strcmp(requested_chal, challenges[idx].day_name))
            {
                return_status = run_day(challenges[idx]);
                found         = true;
                break;
            }
        }

        if (false == found)
        {
            ERROR_LOG("invalid argument");
            printf("%s\n", USAGE_GUIDE);
            return_status = ERROR_INVALID_INPUT;
        }
    }

    return return_status;
}

/*** end of file ***/
