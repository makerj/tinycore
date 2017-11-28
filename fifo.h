#ifndef __UTIL_FIFO_H__
#define __UTIL_FIFO_H__

#include <stddef.h>
#include <stdbool.h>

/**
 * @file
 * First In First Out data structure
 */

/**
 * FIFO data structure
 */
typedef struct _FIFO {
	size_t		head;	///< Head index (internal use only)
	size_t		tail;	///< Tail index (internal use only)
	size_t		size;	///< Array size (internal use only)
	void**		array;	///< FIFO array (internal use only)
	void*		pool;	///< Memory pool (internal use only)
} FIFO;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a FIFO. fifo_init will be called internally.
 *
 * @param size FIFO array size
 * @param pool memory pool, if NULL local memory area will be used
 * @return FIFO
 */
FIFO* fifo_create(size_t size, void* pool);

/**
 * Destroy the FIFO.
 */
void fifo_destroy(FIFO* fifo);

/**
 * Resize the FIFO.
 *
 * @param fifo FIFO
 * @param size the new size
 * @param popped if there is some data in FIFO, popped will be called
 * @return false if there is no more memory to allocate
 */
bool fifo_resize(FIFO* fifo, size_t size, void(*popped)(void*));

/**
 * Initialize the FIFO which is not created using fifo_create function.
 *
 * @param fifo FIFO
 * @param array array to use
 * @param size size of the array
 */
void fifo_init(FIFO* fifo, void** array, size_t size);

/**
 * Replace FIFO's array with new one.
 *
 * @param fifo FIFO
 * @param array the new array to replace the old one
 * @param size the new array's size
 * @param popped every elements in old array will be popped and popped callback will be called
 */
void fifo_reinit(FIFO* fifo, void** array, size_t size, void(*popped)(void*));

/**
 * Push an element to the FIFO.
 * 
 * @param fifo FIFO
 * @param data an element to push to FIFO
 * @return true if the element is pushed to the FIFO
 */
bool fifo_push(FIFO* fifo, void* data);

/**
 * Pop an element from the FIFO.
 *
 * @param fifo FIFO
 * @return popped element or NULL if there is no element in the FIFO
 */
void* fifo_pop(FIFO* fifo);

/**
 * Peek an element from the FIFO.
 *
 * @param fifo FIFO
 * @param index peeking index, zero means the first one
 * @return peeked element or NULL if there is no element in the FIFO or out of bounds
 */
void* fifo_peek(FIFO* fifo, size_t index);

/**
 * Get FIFO's array size.
 *
 * @param fifo FIFO
 * @return fifo's array size
 */
size_t fifo_size(FIFO* fifo);

/**
 * Get capacity (FIFO size - 1).
 *
 * @param fifo FIFO
 * @return get FIFO's capacity which will be FIFO size - 1
 */
size_t fifo_capacity(FIFO* fifo);

/**
 * Check there is available space to push an element.
 *
 * @param fifo FIFO
 * @return true if there is available space
 */
bool fifo_available(FIFO* fifo);

/**
 * Check FIFO is empty or not
 *
 * @param fifo FIFO
 * @return true if FIFO is empty
 */
bool fifo_empty(FIFO* fifo);

#ifdef __cplusplus
}
#endif

#endif /* __UTIL_FIFO_H__ */
