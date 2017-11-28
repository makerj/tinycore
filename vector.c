#include <stddef.h>
#include <stdlib.h>
#include "vector.h"

Vector* vector_create(size_t size, void* pool) {
	Vector* vector = malloc(sizeof(Vector));
	if(!vector)
		return NULL;
	
	void** array = malloc(size * sizeof(void*));
	if(!array) {
		free(vector);
		return NULL;
	}
	vector_init(vector, array, size);
	vector->pool = pool;
	
	return vector;
}

void vector_destroy(Vector* vector) {
	free(vector->array);
	free(vector);
}

void vector_init(Vector* vector, void** array, size_t size) {
	vector->index = 0;
	vector->size = size;
	vector->array = array;
	vector->pool = NULL;
}

bool vector_available(Vector* vector) {
	return vector->index < vector->size;
}

bool vector_is_empty(Vector* vector) {
	return vector->index == 0;
}

bool vector_add(Vector* vector, void* data) {
	if(vector->index >= vector->size) {
		size_t new_size = (size_t) ((vector->size * 1.5) + 1);
		void** array = realloc(vector->array, sizeof(void*) * new_size);
		if (!array)
			return false;

		vector->array = array;
		vector->size = new_size;
	}

	vector->array[vector->index++] = data;
	return true;
}

void* vector_get(Vector* vector, size_t index) {
	if(index >= vector->index)
		return NULL;
	else
		return vector->array[index];
}

bool vector_pack(Vector* vector) {
	void** array = realloc(vector->array, sizeof(void*) * vector->index);
	if (!array)
		return false;

	vector->array = array;
	vector->size = vector->index;
	return true;
}

void* vector_remove_last(Vector* vector) {
	if (vector->index <= 0)
		return NULL;
	else
		return vector->array[--vector->index];
}

void* vector_get_last(Vector* vector) {
	if (vector->index <= 0)
		return NULL;
	else
		return vector->array[vector->index - 1];
}

static bool default_comp_fn(void* v1, void* v2) {
	return v1 == v2;
}

size_t vector_index_of(Vector* vector, void* data, bool(*comp_fn)(void*,void*)) {
	if(!comp_fn)
		comp_fn = default_comp_fn;
	
	for(size_t index = 0; index < vector->index; index++)
		if(comp_fn(vector->array[index], data))
			return index;
	
	return -1;
}

void* vector_remove(Vector* vector, size_t index) {
	if(index >= vector->index) {
		return NULL;
	} else {
		void* data = vector->array[index];
		vector->index--;
		
		while(index < vector->index) {
			vector->array[index] = vector->array[index + 1];
			index++;
		}
		
		return data;
	}
}

size_t vector_size(Vector* vector) {
	return vector->index;
}

size_t vector_capacity(Vector* vector) {
	return vector->size;
}

void vector_iterator_init(VectorIterator* iter, Vector* vector) {
	iter->vector = vector;
	iter->index = 0;
}

bool vector_iterator_has_next(VectorIterator* iter) {
	return iter->index < iter->vector->index;
}

void* vector_iterator_next(VectorIterator* iter) {
	if(iter->index < iter->vector->index)
		return iter->vector->array[iter->index++];
	else
		return NULL;
}

void* vector_iterator_remove(VectorIterator* iter) {
	if(--iter->index < iter->vector->index)
		return vector_remove(iter->vector, iter->index);
	else
		return NULL;
}
