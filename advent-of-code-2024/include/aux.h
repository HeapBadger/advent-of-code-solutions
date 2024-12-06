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

#define ERROR_LOG(msg)                                                         \
  do {                                                                         \
    fprintf(stderr, "%s\n", msg);                                              \
  } while (0)

#endif // AUX_H
