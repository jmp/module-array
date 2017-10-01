#include <stdlib.h>
#include "array.h"

/* Optionally, use the memory module */
#ifdef USE_MEMORY
	#include "memory.h"
#else
	#define memory_malloc malloc
	#define memory_realloc realloc
	#define memory_free free
#endif

/* Defines how many elements the array can store initially */
#define ARRAY_INITIAL_CAPACITY 16

/* Capacity is increased by this factor when the array gets full */
#define ARRAY_GROWTH_FACTOR 2

struct Array {
	int length;
	int capacity;
	void **elements;
};

/*
 * Increase the capacity of the given array.
 * Returns 1 if everything went fine, 0 if reallocation fails.
 */
static int array_grow(Array *array) {
	const int new_capacity = array->capacity * ARRAY_GROWTH_FACTOR;
	const int new_elements_size = sizeof(array->elements) * array->capacity;
	void *new_elements = memory_realloc(array->elements, new_elements_size);

	if (new_elements == NULL) {
		return 0;
	}

	array->elements = new_elements;
	array->capacity = new_capacity;

	return 1;
}

Array *array_create(void) {
	Array *array = memory_malloc(sizeof(Array));

	if (array != NULL) {
		array->length = 0;
		array->capacity = ARRAY_INITIAL_CAPACITY;
		array->elements = memory_malloc(sizeof(array->elements) * array->capacity);

		if (array->elements == NULL) {
			/* Free whatever we allocated already */
			memory_free(array);
			array = NULL;
		}
	}

	return array;
}

void array_free(Array *array) {
	if (array != NULL) {
		memory_free(array->elements);
		array->elements = NULL;
	}
	memory_free(array);
}

int array_length(Array *array) {
	if (array != NULL) {
		return array->length;
	}
	return 0;
}

int array_capacity(Array *array) {
	if (array != NULL) {
		return array->capacity;
	}
	return 0;
}

int array_insert(Array *array, int index, void *element) {
	int i;

	/*
	 * If we are trying to insert past the bounds, do nothing,
	 * unless the index is exactly the length of the array, in
	 * which case we will insert to the end.
	 */
	if (array == NULL || index < 0 || index > array->length) {
		return 0;
	}

	/* Grow if needed */
	if (array->length >= array->capacity && !array_grow(array)) {
		return 0; /* Out of memory */
	}

	/* Shift elements forward, starting from the end */
	for (i = array->length; i > index; --i) {   
		array->elements[i] = array->elements[i - 1];
	}

	/* Insert at the given index */
	array->elements[index] = element;
	array->length++;

	return 1;
}

void *array_remove(Array *array, int index) {
	/* Make sure we won't delete past the bounds */
	if (array != NULL && index >= 0 && index < array->length) {
		int i;
		void *element = array->elements[index];
		/* Shift elements backwards, starting at the given index */
		for (i = index; i < array->length - 1; ++i) {
			array->elements[i] = array->elements[i + 1];
		}
		array->elements[--array->length] = NULL;
		return element;
	}

	return NULL;
}

int array_push(Array *array, void *element) {
	if (array != NULL) {
		return array_insert(array, array->length, element);
	}
	return 0;
}

void *array_pop(Array *array) {
	if (array != NULL) {
		return array_remove(array, array->length - 1);
	}
	return NULL;
}

void *array_get(Array *array, int index) {
	if (array != NULL && index >= 0 && index < array->length) {
		return array->elements[index];
	}
	return NULL;
}

int array_set(Array *array, int index, void *element) {
	if (array != NULL && index >= 0 && index < array->length) {
		array->elements[index] = element;
		return 1;
	}
	return 0;
}

void *array_last(Array *array) {
	if (array != NULL && array->length > 0) {
		return array_get(array, array->length - 1);
	}
	return NULL;
}

void array_sort(Array *array, int (*cmp)(const void*, const void*)) {
	if (array != NULL && cmp != NULL) {
		qsort(array->elements, array_length(array), sizeof(void*), cmp);
	}
}
