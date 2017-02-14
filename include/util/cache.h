#ifndef __UTIL_CACHE_H__
#define __UTIL_CACHE_H__

#include <util/list.h>
#include <util/map.h>

typedef struct {
	Map*	map;
	List*	list;
	size_t 	capacity;
	void	(*uncache)(void*);
	void*	pool;
} Cache;

Cache* cache_create(size_t capacity, void(*uncache)(void*), void* pool);
void cache_destroy(Cache* cache);
void* cache_get(Cache* cache, void* key);
bool cache_set(Cache* cache, void* key, void* data);
void* cache_remove(Cache* cache, void* key);
void cache_clear(Cache* cache);

typedef struct _CacheIterator {
	Cache* cache;
	ListNode* node;			
} CacheIterator;

void cache_iterator_init(CacheIterator* iter, Cache* cache);
bool cache_iterator_has_next(CacheIterator* iter);
void* cache_iterator_next(CacheIterator* iter);

#endif /* __UTIL_CACHE_H__ */

