#ifndef AUX_H
#define AUX_H

#include <stdio.h>

/**
 * @file aux.h
 * @brief Auxiliary utilities and definitions for the project.
 *
 * This header file contains macro definitions and utility declarations
 * used for error handling, logging, and common configurations across
 * the project.
 */

/**
 * @brief Logs an error message to `stderr`.
 *
 * This macro prints an error message to the standard error stream.
 *
 * @param msg The error message to be logged.
 */
#define ERROR_LOG(msg)                \
    do                                \
    {                                 \
        fprintf(stderr, "%s\n", msg); \
    } while (0)

/**
 * @brief Maximum size for buffer input.
 *
 * Defines the maximum buffer size for reading input lines from files
 * or other sources.
 */
#define BUFFER_SIZE 4096

#endif // AUX_H
