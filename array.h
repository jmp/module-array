/*
 * A simple, generic implementation of a dynamically sized array. It uses
 * a pointer array as the basis and maintains the order of the elements
 * when inserting or removing.
 *
 * Insertion and removal at the end as well as look-up by index are
 * constant-time operations. Inserting or removing in the middle takes
 * linear time since the following elements have to be shifted. Length
 * can also retrieved in constant time. Sorting is done by the standard
 * library qsort function.
 *
 * The array automatically reallocates when it gets full. By default, the
 * capacity is doubled.
 */

#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array Array;

/*
 * Allocate memory for the new array and return it.
 * Returns a pointer to the newly allocated element,
 * or NULL if we ran out of memory.
 */
extern Array *array_create(void);

/*
 * Destroy the array and free any allocated memory.
 */
extern void array_free(Array *array);

/*
 * Get the length of the array.
 * The length of a NULL array is zero.
 */
extern int array_length(Array *array);

/*
 * Get the capacity of the array.
 * The capacity of a NULL array is zero.
 */
extern int array_capacity(Array *array);

/*
 * Insert the given element into the array at the given index.
 * Returns 1 if the insertion was successful, 0 otherwise. If the
 * array does not have enough capacity, it will be resized. When
 * adding elements to the middle of the array, the remaining
 * elements will be shifted. Therefore insertion is a linear-time
 * operation.
 */
extern int array_insert(Array *array, int index, void *element);

/*
 * Remove the element at the given index from the array.
 * This is a linear-time operation: when the element is removed,
 * the following elements are shifted backwards by one. Returns
 * the element that was removed, or NULL if there was no element
 * in the array at that index.
 */
extern void *array_remove(Array *array, int index);

/*
 * Add the given element to the end of the array.
 * This is a constant-time operation.
 */
extern int array_push(Array *array, void *element);

/*
 * Pop the last element off the end of the array and return it.
 * Returns NULL if the array is empty.
 */
extern void *array_pop(Array *array);

/*
 * Get the element from the array at the given index.
 * Returns NULL if there is nothing in that index.
 */
extern void *array_get(Array *array, int index);

/*
 * Sets (replaces) the element at the given index.
 * Returns 1 if the set succeeded, 0 otherwise.
 */
extern int array_set(Array *array, int index, void *element);

/*
 * Get the last element in the array.
 * Returns NULL if the array is empty.
 */
extern void *array_last(Array *array);

/*
 * Sort the array with the given comparison function.
 * Internally, simply uses qsort, so the time complexity
 * depends on its implementation.
 */
extern void array_sort(Array *array, int (*cmp)(const void*, const void*));

#endif /* ARRAY_H */
