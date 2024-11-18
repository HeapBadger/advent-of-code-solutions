#ifndef AUX_H
#define AUX_H

/**
 * @file aux.h
 * @brief Auxiliary utilities and definitions for the project.
 *
 * This header file contains auxiliary function declarations and macro
 * definitions that are used across the project to provide common utilities and
 * helpers.
 */

#include <stdio.h>

/**
 * @def ERROR_LOG(msg)
 * @brief Logs an error message with a standard format.
 *
 * This macro is used to print error messages to the standard output.
 * It prepends the message with a consistent `[!] ERROR: ` prefix for clarity.
 *
 * Example usage:
 * @code
 * ERROR_LOG("unable to open file");
 * @endcode
 *
 * Output:
 * @code
 * [!] ERROR: unable to open file
 * @endcode
 *
 * @param msg A string literal or a null-terminated string containing the error
 * message.
 */
#define ERROR_LOG(msg) printf("[!] ERROR: %s\n", msg)

#endif // AUX_H
