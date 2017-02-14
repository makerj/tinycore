#ifndef __UTIL_SET_H__
#define __UTIL_SET_H__

#include <stdint.h>
#include "list.h"

/**
 * @file
 * Hash Set data structure
 */

/**
 * Hash set entry data structure (internal use only)
 */
typedef struct _SetEntry {
	void*	data;			///< Value
} SetEntry;

/**
 * Hash Set data structure
 */
typedef struct _Set {
	List**		table;		///< Set table (internal use only)
	size_t		threshold;	///< Threshold to extend the table (internal use only)
	size_t		capacity;	///< Current capacity (internal use only)
	size_t		size;		///< Number of elements (internal use only)
	
	uint64_t(*hash)(void*);		///< hashing function
	bool(*equals)(void*,void*);	///< comparing function
	
	void*		pool;		///< Memory pool (internal use only)
} Set;

/**
 * Create a HashSet.
 *
 * @param initial_capacity respected maximum number of elements
 * @param hash data hashing function, if hash is NULL set_uint64_hash will be used
 * @param equals data comparing function, if equals is NULL set_uint64_equals will be used
 * @param pool memory pool to use, if NULL local memory area will be used
 */
Set* set_create(size_t initial_capacity, uint64_t(*hash)(void*), bool(*equals)(void*,void*), void* pool);

/**
 * Destroy the HashSet.
 *
 * @param set HashSet
 */
void set_destroy(Set* set);

/**
 * Check the HashSet is empty or not.
 *
 * @param set HashSet
 * @return true if the HashSet is empty
 */
bool set_is_empty(Set* set);

/**
 * Put an element to the HashSet.
 *
 * @param set HashSet
 * @param data key of element
 * @param data data of element
 * @return true if the element is putted, false if there is an element with same data or memory is full
 */
bool set_put(Set* set, void* data);

/**
 * Get an element data from the HashSet.
 *
 * @param set HashSet
 * @param data key of the element
 * @return the element's data or NULL if there is no such element
 */
void* set_get(Set* set, void* data);

/**
 * Check there is an element.
 *
 * @param set HashSet
 * @param data key of the element
 * @return true if there is an element with the data
 */
bool set_contains(Set* set, void* data);

/**
 * Remove an element from the HashSet.
 *
 * @param set HashSet
 * @param data key of the element
 * @return removed element or NULL if nothing is removed
 */
void* set_remove(Set* set, void* data);

/**
 * Get the current capacity of the HashSet.
 *
 * @param set HashSet
 * @return capacity of the HashSet
 */
size_t set_capacity(Set* set);

/**
 * Get the number of elements of the HashSet.
 *
 * @param set HashSet
 * @return number of elements
 */
size_t set_size(Set* set);

/**
 * Iterator of a HashSet
 */
typedef struct _SetIterator {
	Set*		set;		///< HashSet (internal use only)
	size_t		index;		///< Current index of table (internal use only)
	size_t		list_index;	///< Current index of list (internal use only)
	SetEntry	entry;		///< Temporary SetEntry
} SetIterator;

/**
 * Initialize the iterator.
 *
 * @param iter the iterator
 * @param set HashSet
 */
void set_iterator_init(SetIterator* iter, Set* set);

/**
 * Check there is more element to iterate.
 *
 * @param iter iterator
 * @return true if there is more element to iterate
 */
bool set_iterator_has_next(SetIterator* iter);

/**
 * Get next element from iterator.
 *
 * @param iter iterator
 * @return next element (SetEntry)
 */
SetEntry* set_iterator_next(SetIterator* iter);

/**
 * Remove the element from the HashSet which is recetly iterated using set_iterator_next function.
 *
 * @param iter iterator
 * @return removed element (SetEntry)
 */
SetEntry* set_iterator_remove(SetIterator* iter);

/**
 * unsigned integer 64-bits hashing function
 *
 * @param data key of an element
 * @return hashed value of the data
 */
uint64_t set_uint64_hash(void* data);

/**
 * unsigned integer 64-bits comparing function
 *
 * @param data1 key of an element
 * @param data2 key of another element
 * @return true if two datas are same
 */
bool set_uint64_equals(void* data1, void* data2);

/**
 * C string hashing function
 *
 * @param data key of an element
 * @return hashed value of the data
 */
uint64_t set_string_hash(void* data);

/**
 * C string comparing function
 *
 * @param data1 key of an element
 * @param data2 key of another element
 * @return true if two datas are same
 */
bool set_string_equals(void* data1, void* data2);

#endif /* __UTIL_SET_H__ */
