#ifndef __UTIL_VECTOR_H__
#define __UTIL_VECTOR_H__

#include <stddef.h>
#include <stdbool.h>

/**
 * @file
 * Array wrapper data structure
 */

/**
 * Vector (or array) data structure
 */
typedef struct _Vector {
	size_t		index;	///< Element index (internal use only)
	size_t		size;	///< Array size (internal use only)
	void**		array;	///< Array itself (internal use only)
	void*		pool;	///< Memory pool (internal use only)
} Vector;

/**
 * Create a Vector. vector_init will be called internally.
 *
 * @param size size of Vector
 * @param pool memory pool to use, if NULL local memory area will be used
 */
Vector* vector_create(size_t size, void* pool);

/**
 * Destroy the Vector.
 *
 * @param vector Vector
 */
void vector_destroy(Vector* vector);

/**
 * Initialize the Vector which is not created using vector_create function.
 *
 * @param vector Vector
 * @param array array to use
 * @param size size of the array
 */
void vector_init(Vector* vector, void** array, size_t size);

/**
 * Check there is available space to add an element.
 *
 * @param vector Vector
 * @return true if there is available space
 */
bool vector_available(Vector* vector);

/**
 * Check the Vector is empty or not.
 *
 * @param vector Vector
 * @return true if the Vector is empty
 */
bool vector_is_empty(Vector* vector);

/**
 * Add an element to the Vector.
 *
 * @param vector Vector
 * @param data an element to add
 * @return true if the element is added
 */
bool vector_add(Vector* vector, void* data);

/**
 * Get an element from the Vector.
 *
 * @param vector Vector
 * @param index element index
 * @return an element or NULL if index is out of bounds
 */
void* vector_get(Vector* vector, size_t index);

/**
 * Pack the Vector.
 * @param vector vector
 */
bool vector_pack(Vector* vector);

/**
 * Remove last element from the vector
 * @param vector vector
 * @return last element or NULL if there is no element
 */
void* vector_remove_last(Vector* vector);

/**
 * Get last element from the vector
 * @param vector vector;
 * @return last element or NULL if there is no element
 */
void* vector_get_last(Vector* vector);

/**
 * Get index of an element using comparing function.
 *
 * @param vector Vector
 * @param data the element to compare
 * @param comp_fn comparing function to check the data is equal or not, if NULL pointer comparing is used
 * @return index of the element, -1 if noting is matched
 */
size_t vector_index_of(Vector* vector, void* data, bool(*comp_fn)(void*,void*));

/**
 * Remove an element from the Vector.
 *
 * @param vector Vector
 * @param index index of the element
 * @return removed element or NULL if nothing is removed
 */
void* vector_remove(Vector* vector, size_t index);

/**
 * Get the number of elements of the Vector.
 *
 * @param vector Vector
 * @return size of the Vector
 */
size_t vector_size(Vector* vector);

/**
 * Get the capacity of the Vector.
 *
 * @param vector Vector
 * @return capacity size of the Vector
 */
size_t vector_capacity(Vector* vector);

/**
 * Iterator of a Vector.
 */
typedef struct _VectorIterator {
	Vector* vector;			///< Vector (internal use only)
	size_t index;			///< current position (internal use only)
} VectorIterator;

/**
 * Initialize the iterator.
 *
 * @param iter the iterator
 * @param vector Vector
 */
void vector_iterator_init(VectorIterator* iter, Vector* vector);

/**
 * Check there is more element to iterate.
 *
 * @param iter iterator
 * @return true if there is more element to iterate
 */
bool vector_iterator_has_next(VectorIterator* iter);

/**
 * Get next element from iterator.
 *
 * @param iter iterator
 * @return next element
 */
void* vector_iterator_next(VectorIterator* iter);

/**
 * Remove the element from the Vector which is recetly iterated using vecotr_iterator_next function.
 *
 * @param iter iterator
 * @return removed element
 */
void* vector_iterator_remove(VectorIterator* iter);

#endif /* __UTIL_VECTOR_H__ */
