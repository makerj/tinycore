#ifndef __UTIL_MAP_H__
#define __UTIL_MAP_H__

#include <stdint.h>
#include "list.h"

/**
 * @file
 * Hash Map data structure
 */

/**
 * Hash map entry data structure (internal use only)
 */
typedef struct _MapEntry {
	void*	key;			///< Key
	void*	data;			///< Value
} MapEntry;

/**
 * Hash Map data structure
 */
typedef struct _Map {
	List**		table;		///< Map table (internal use only)
	size_t		threshold;	///< Threshold to extend the table (internal use only)
	size_t		capacity;	///< Current capacity (internal use only)
	size_t		size;		///< Number of elements (internal use only)
	
	uint64_t(*hash)(void*);		///< hashing function
	bool(*equals)(void*,void*);	///< comparing function
	
	void*		pool;		///< Memory pool (internal use only)
} Map;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a HashMap.
 *
 * @param initial_capacity respected maximum number of elements
 * @param hash key hashing function, if hash is NULL map_uint64_hash will be used
 * @param equals key comparing function, if equals is NULL map_uint64_equals will be used
 * @param pool memory pool to use, if NULL local memory area will be used
 */
Map* map_create(size_t initial_capacity, uint64_t(*hash)(void*), bool(*equals)(void*,void*), void* pool);

/**
 * Destroy the HashMap.
 *
 * @param map HashMap
 */
void map_destroy(Map* map);

/**
 * Check the HashMap is empty or not.
 *
 * @param map HashMap
 * @return true if the HashMap is empty
 */
bool map_is_empty(Map* map);

/**
 * Put an element to the HashMap.
 *
 * @param map HashMap
 * @param key key of element
 * @param data data of element
 * @return true if the element is putted, false if there is an element with same key or memory is full
 */
bool map_put(Map* map, void* key, void* data);

/**
 * Update an element with new key and data.
 *
 * @param map HashMap
 * @param key new key of the element
 * @param data new data of the element
 * @return true if the element is updated, false if there is no such element
 */
bool map_update(Map* map, void* key, void* data);

/**
 * Get an element data from the HashMap.
 *
 * @param map HashMap
 * @param key key of the element
 * @return the element's data or NULL if there is no such element
 */
void* map_get(Map* map, void* key);

/**
 * Get an element key from the HashMap.
 *
 * @param map HashMap
 * @param key key of the element
 * @return the element's key or NULL if there is no such element
 */
void* map_get_key(Map* map, void* key);

/**
 * Check there is an element.
 *
 * @param map HashMap
 * @param key key of the element
 * @return true if there is an element with the key
 */
bool map_contains(Map* map, void* key);

/**
 * Remove an element from the HashMap.
 *
 * @param map HashMap
 * @param key key of the element
 * @return removed element or NULL if nothing is removed
 */
void* map_remove(Map* map, void* key);

/**
 * Get the current capacity of the HashMap.
 *
 * @param map HashMap
 * @return capacity of the HashMap
 */
size_t map_capacity(Map* map);

/**
 * Get the number of elements of the HashMap.
 *
 * @param map HashMap
 * @return number of elements
 */
size_t map_size(Map* map);

/**
 * Iterator of a HashMap
 */
typedef struct _MapIterator {
	Map*		map;		///< HashMap (internal use only)
	size_t		index;		///< Current index of table (internal use only)
	size_t		list_index;	///< Current index of list (internal use only)
	MapEntry	entry;		///< Temporary MapEntry
} MapIterator;

/**
 * Initialize the iterator.
 *
 * @param iter the iterator
 * @param map HashMap
 */
void map_iterator_init(MapIterator* iter, Map* map);

/**
 * Check there is more element to iterate.
 *
 * @param iter iterator
 * @return true if there is more element to iterate
 */
bool map_iterator_has_next(MapIterator* iter);

/**
 * Get next element from iterator.
 *
 * @param iter iterator
 * @return next element (MapEntry)
 */
MapEntry* map_iterator_next(MapIterator* iter);

/**
 * Remove the element from the HashMap which is recetly iterated using map_iterator_next function.
 *
 * @param iter iterator
 * @return removed element (MapEntry)
 */
MapEntry* map_iterator_remove(MapIterator* iter);

/**
 * unsigned integer 64-bits hashing function
 *
 * @param key key of an element
 * @return hashed value of the key
 */
uint64_t map_uint64_hash(void* key);

/**
 * unsigned integer 64-bits comparing function
 *
 * @param key1 key of an element
 * @param key2 key of another element
 * @return true if two keys are same
 */
bool map_uint64_equals(void* key1, void* key2);

/**
 * C string hashing function
 *
 * @param key key of an element
 * @return hashed value of the key
 */
uint64_t map_string_hash(void* key);

/**
 * C string comparing function
 *
 * @param key1 key of an element
 * @param key2 key of another element
 * @return true if two keys are same
 */
bool map_string_equals(void* key1, void* key2);

#ifdef __cplusplus
}
#endif

#endif /* __UTIL_MAP_H__ */
