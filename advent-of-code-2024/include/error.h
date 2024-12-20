#ifndef ERROR_H
#define ERROR_H

/**
 * @file error.h
 * @brief Custom error codes and definitions.
 *
 * This header file contains integer error codes for consistent error
 * handling across the application. Negative values indicate errors,
 * while `0` indicates success.
 */

/* Success */
#define ERROR_SUCCESS 0 /**< Operation completed successfully */

/* General Errors */
#define ERROR_UNKNOWN             -1 /**< Unknown error occurred */
#define ERROR_INVALID_INPUT       -2 /**< Input value is invalid */
#define ERROR_OUT_OF_MEMORY       -3 /**< Memory allocation failed */
#define ERROR_NULL_POINTER        -4 /**< Null pointer dereferenced */
#define ERROR_INDEX_OUT_OF_BOUNDS -5 /**< Index is out of valid range */
#define ERROR_ELEMENT_NOT_FOUND   -6 /**< Element does not exist */

/* File Handling Errors */
#define ERROR_FILE_NOT_FOUND -100 /**< File not found */
#define ERROR_FILE_READ      -101 /**< Failed to read from file */
#define ERROR_FILE_WRITE     -102 /**< Failed to write to file */

/* Network Errors */
#define ERROR_CONNECTION_FAIL -200 /**< Network connection failed */
#define ERROR_TIMEOUT         -201 /**< Operation timed out */

#endif // ERROR_H
