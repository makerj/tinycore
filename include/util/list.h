#ifndef __UTIL_LIST_H__
#define __UTIL_LIST_H__

#include <stddef.h>
#include <stdbool.h>

/**
 * @file
 * Double Linked List data structure
 */

/**
 * List Node data structure (internal use only)
 */
typedef struct _ListNode {
	struct _ListNode*	prev;	///< Previous node
	struct _ListNode*	next;	///< Next node
	void*			data;	///< User data
} ListNode;

/**
 * Linked List data structure
 */
typedef struct _List {
	ListNode*	head;	///< Header node (internal use only)
	ListNode*	tail;	///< Tail node (internal use only)
	size_t		size;	///< Number of elements (internal use only)
	void*		pool;	///< Memory pool (internal use only)
} List;

/**
 * Create a LinkedList.
 *
 * @param pool memory pool to use, if NULL local memory area will be used
 */
List* list_create(void* pool);

/**
 * Destroy the LinkedList.
 *
 * @param list LinkedList
 */
void list_destroy(List* list);

/**
 * Check the LinkedList is empty or not.
 *
 * @param list LinkedList
 * @return true if the LinkedList is empty
 */
bool list_is_empty(List* list);

/**
 * Add an element to the LinkedList.
 *
 * @param list LinkedList
 * @param data an element to add
 * @return true if the element is added
 */
bool list_add(List* list, void* data);

/**
 * Add an element to the LinkedList with specific index.
 * If the index is less than zero, the element will be added to the head.
 * If the index excceds the last element, the element will be added to the tail.
 *
 * @param list LinkedList
 * @param index index of the element
 * @param data an element to add
 * @return true if the element is added
 */
bool list_add_at(List* list, size_t index, void* data);

/**
 * Get an element from the LinkedList.
 *
 * @param list LinkedList
 * @param index element index
 * @return an element or NULL if index is out of bounds
 */
void* list_get(List* list, size_t index);

/**
 * Get the first element from the LinkedList.
 *
 * @param list LinkedList
 * @return an element or NULL if there is no element
 */
void* list_get_first(List* list);

/**
 * Get the last element from the LinkedList.
 *
 * @param list LinkedList
 * @return an element or NULL if there is no element
 */
void* list_get_last(List* list);

/**
 * Get index of an element using comparing function.
 *
 * @param list LinkedList
 * @param data the element to compare
 * @param comp_fn comparing function to check the data is equal or not, if NULL pointer comparing is used
 * @return index of the element, -1 if noting is matched
 */
int list_index_of(List* list, void* data, bool(*comp_fn)(void*,void*));

/**
 * Remove an element from the LinkedList.
 *
 * @param list LinkedList
 * @param index index of the element
 * @return removed element or NULL if nothing is removed
 */
void* list_remove(List* list, size_t index);

/**
 * Remove an element which has same pointer of data from the LinkedList.
 *
 * @param list LinkedList
 * @param data the pointer to compare with elements
 * @return removed element or NULL if nothing is removed
 */
bool list_remove_data(List* list, void* data);

/**
 * Remove the first element from the LinkedList.
 *
 * @param list LinkedList
 * @return removed element or NULL if the LinkedList is empty
 */
void* list_remove_first(List* list);

/**
 * Remove the last element from the LinkedList.
 *
 * @param list LinkedList
 * @return removed element or NULL if the LinkedList is empty
 */
void* list_remove_last(List* list);

/**
 * Get the number of elements of the LinkedList.
 *
 * @param list LinkedList
 * @return size of the LinkedList
 */
size_t list_size(List* list);

/**
 * Move the first element to the end.
 *
 * @param list LinkedList
 */
void list_rotate(List* list);

/**
 * Iterator of a LinkedList.
 */
typedef struct _ListIterator {
	List* list;			///< LinkedList (internal use only)
	ListNode* prev;			///< previous node (internal use only)
	ListNode* node;			///< current node (internal use only)
} ListIterator;

/**
 * Initialize the iterator.
 *
 * @param iter the iterator
 * @param list LinkedList
 */
void list_iterator_init(ListIterator* iter, List* list);

/**
 * Check there is more element to iterate.
 *
 * @param iter iterator
 * @return true if there is more element to iterate
 */
bool list_iterator_has_next(ListIterator* iter);

/**
 * Get next element from iterator.
 *
 * @param iter iterator
 * @return next element
 */
void* list_iterator_next(ListIterator* iter);

/**
 * Remove the element from the LinkedList which is recetly iterated using list_iterator_next function.
 *
 * @param iter iterator
 * @return removed element
 */
void* list_iterator_remove(ListIterator* iter);

#endif /* __UTIL_LIST_H__ */
