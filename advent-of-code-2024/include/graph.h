#ifndef GRAPH_H
#define GRAPH_H

/**
 * @file graph.h
 * @brief Graph utilities and definitions.
 *
 * This header file contains function declarations and macro definitions for
 * the graph source file.
 */

/**
 * @enum ElementType
 * @brief Defines the supported types for elements stored in the graph.
 *
 * This enum is used to identify the type of the elements that are stored in
 * the grraph node.
 */
typedef enum
{
    TYPE_INT,     /**< Integer type */
    TYPE_FLOAT,   /**< Float type */
    TYPE_DOUBLE,  /**< Double type */
    TYPE_CHAR,    /**< Character type */
    TYPE_INT_PTR, /**< Pointer type */
} ElementType;

/**
 * @brief Structure to represent an graph with dynamic size.
 *
 * The graph is capable of holding any data type, with the actual data stored as
 * void pointers.
 */
typedef struct
{
    void **list; /**< Pointer to the graph of elements.*/
    int    idx;  /**< Current index (number of elements stored in the graph). */
    int    max;  /**< Maximum capacity of the graph. */
    ElementType ele_type; /**< The type of the elements stored in the graph. */
} graph;

/**
 * @brief Initializes an empty graph.
 *
 * This function allocates memory for the graph and sets up the initial
 * capacity. The elements are initialized to NULL to indicate empty slots.
 *
 * @param ele_type The type of elements stored in the graph.
 * @return Pointer to the newly created graph, or NULL on failure.
 */
graph *graph_initialization(ElementType ele_type);

/**
 * @brief Destroys the graph, freeing allocated memory.
 *
 * This function frees the memory for both the graph and its elements.
 * Each element is assumed to have been dynamically allocated and will be freed.
 *
 * @param graph Pointer to the graph to be destroyed.
 */
void graph_destroy(graph *graph);

#endif // GRAPH_H
