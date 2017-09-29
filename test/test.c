#include "test.h"
#include "array.h"

/* For sorting test */
static int compare(const void *a, const void *b)
{
    return **(int**) a - **(int**) b;
}

static int test_array_create(void)
{
    Array *array = array_create();
    test_assert(array != NULL);
    test_assert(array_length(array) == 0);
    test_assert(array_capacity(array) > 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_create_no_memory(void)
{
    Array *array;
    test_malloc_disable();
    array = array_create();
    test_malloc_enable();
    test_assert(array == NULL);
    array_free(array);

    return TEST_PASS;
}

static int test_array_create_no_memory_for_elements(void)
{
    Array *array;
    test_malloc_fail_after(1); /* Fail when allocating elements */
    array = array_create();
    test_malloc_enable();
    test_assert(array == NULL);
    array_free(array);

    return TEST_PASS;
}

static int test_array_length_of_empty(void)
{
    Array *array = array_create();
    test_assert(array_length(array) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_length_of_null(void)
{
    test_assert(array_length(NULL) == 0);

    return TEST_PASS;
}

static int test_array_insert_adds_null(void)
{
    Array *array = array_create();
    array_insert(array, 0, NULL);
    test_assert(array_get(array, 0) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_insert_out_of_bounds(void)
{
    Array *array = array_create();
    test_assert(array_length(array) == 0);
    array_insert(array, -1, NULL);
    test_assert(array_length(array) == 0);
    array_insert(array, 1, NULL);
    test_assert(array_length(array) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_insert_increases_length(void)
{
    Array *array = array_create();
    test_assert(array_length(array) == 0);
    array_insert(array, 0, NULL);
    test_assert(array_length(array) == 1);
    array_insert(array, 1, NULL);
    test_assert(array_length(array) == 2);
    array_insert(array, 0, NULL);
    test_assert(array_length(array) == 3);
    array_insert(array, 1, NULL);
    test_assert(array_length(array) == 4);
    array_free(array);

    return TEST_PASS;
}

static int test_array_insert_to_null(void)
{
    test_assert(array_insert(NULL, 0, NULL) == 0);

    return TEST_PASS;
}

static int test_array_insert_at_beginning(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_insert(array, 0, &a[0]);
    array_insert(array, 0, &a[1]);
    array_insert(array, 0, &a[2]);
    test_assert(array_get(array, 0) == &a[2]);
    test_assert(array_get(array, 1) == &a[1]);
    test_assert(array_get(array, 2) == &a[0]);
    array_free(array);

    return TEST_PASS;
}

static int test_array_insert_at_middle(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_insert(array, 0, &a[0]);
    array_insert(array, 1, &a[1]);
    array_insert(array, 1, &a[2]);
    test_assert(array_get(array, 0) == &a[0]);
    test_assert(array_get(array, 1) == &a[2]);
    test_assert(array_get(array, 2) == &a[1]);
    array_free(array);

    return TEST_PASS;
}

static int test_array_insert_at_end(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_insert(array, 0, &a[0]);
    array_insert(array, 1, &a[1]);
    array_insert(array, 2, &a[2]);
    test_assert(array_get(array, 0) == &a[0]);
    test_assert(array_get(array, 1) == &a[1]);
    test_assert(array_get(array, 2) == &a[2]);
    array_free(array);

    return TEST_PASS;
}

static int test_array_remove_from_beginning(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    array_push(array, &a[2]);
    test_assert(array_length(array) == 3);
    test_assert(array_remove(array, 0) == &a[0]);
    test_assert(array_get(array, 0) == &a[1]);
    test_assert(array_get(array, 1) == &a[2]);
    test_assert(array_length(array) == 2);
    array_free(array);

    return TEST_PASS;
}

static int test_array_remove_from_middle(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    array_push(array, &a[2]);
    test_assert(array_length(array) == 3);
    test_assert(array_remove(array, 1) == &a[1]);
    test_assert(array_get(array, 0) == &a[0]);
    test_assert(array_get(array, 1) == &a[2]);
    test_assert(array_length(array) == 2);
    array_free(array);

    return TEST_PASS;
}

static int test_array_remove_from_end(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    array_push(array, &a[2]);
    test_assert(array_length(array) == 3);
    test_assert(array_remove(array, 2) == &a[2]);
    test_assert(array_get(array, 0) == &a[0]);
    test_assert(array_get(array, 1) == &a[1]);
    test_assert(array_length(array) == 2);
    array_free(array);

    return TEST_PASS;
}

static int test_array_remove_out_of_bounds(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    array_push(array, &a[2]);
    test_assert(array_remove(array, -1) == NULL);
    test_assert(array_remove(array, 3) == NULL);
    test_assert(array_length(array) == 3);
    array_free(array);

    return TEST_PASS;
}

static int test_array_remove_decreases_length(void)
{
    int a[] = {1, 2, 3};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    array_push(array, &a[2]);
    test_assert(array_length(array) == 3);
    test_assert(array_remove(array, 0) == &a[0]);
    test_assert(array_length(array) == 2);
    test_assert(array_remove(array, 0) == &a[1]);
    test_assert(array_length(array) == 1);
    test_assert(array_remove(array, 0) == &a[2]);
    test_assert(array_length(array) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_remove_from_null(void)
{
    test_assert(array_remove(NULL, 0) == NULL);

    return TEST_PASS;
}

static int test_array_push_adds_to_end(void)
{
    int a[] = {1, 2};
    Array *array = array_create();
    array_push(array, &a[0]);
    test_assert(array_last(array) == &a[0]);
    array_push(array, &a[1]);
    test_assert(array_last(array) == &a[1]);
    array_free(array);

    return TEST_PASS;
}

static int test_array_push_adds_null(void)
{
    Array *array = array_create();
    test_assert(array_length(array) == 0);
    test_assert(array_push(array, NULL) == 1);
    test_assert(array_get(array, 0) == NULL);
    test_assert(array_length(array) == 1);
    array_free(array);

    return TEST_PASS;
}

static int test_array_push_increases_length(void)
{
    Array *array = array_create();
    test_assert(array_length(array) == 0);
    array_push(array, NULL);
    test_assert(array_length(array) == 1);
    array_push(array, NULL);
    test_assert(array_length(array) == 2);
    array_free(array);

    return TEST_PASS;
}

static int test_array_push_to_null(void)
{
    test_assert(array_push(NULL, NULL) == 0);

    return TEST_PASS;
}

static int test_array_capacity_increases(void)
{
    int i, initial_capacity;
    Array *array = array_create();
    initial_capacity = array_capacity(array);
    test_assert(initial_capacity > 0);
    /* Fill up to capacity */
    for (i = array_length(array); i < initial_capacity; i++) {
        array_push(array, NULL);
    }
    /* Capacity should not have increased yet */
    test_assert(array_capacity(array) == initial_capacity);
    /* Adding one more should cause reallocation */
    test_assert(array_push(array, NULL) == 1);
    test_assert(array_capacity(array) > initial_capacity);
    array_free(array);

    return TEST_PASS;
}

static int test_array_capacity_no_memory(void)
{
    int i, initial_capacity;
    Array *array = array_create();
    initial_capacity = array_capacity(array);
    for (i = array_length(array); i < initial_capacity; i++) {
        array_push(array, NULL);
    }
    test_assert(array_capacity(array) == initial_capacity);
    test_realloc_disable();
    test_assert(array_push(array, NULL) == 0);
    test_realloc_enable();
    test_assert(array_capacity(array) == initial_capacity);
    array_free(array);

    return TEST_PASS;
}

static int test_array_capacity_of_empty(void)
{
    Array *array = array_create();
    test_assert(array_capacity(array) > 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_capacity_of_null(void)
{
    test_assert(array_capacity(NULL) == 0);

    return TEST_PASS;
}

static int test_array_pop_returns_element(void)
{
    int a[] = {1, 2};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    test_assert(array_length(array) == 2);
    test_assert((int*) array_pop(array) == &a[1]);
    test_assert((int*) array_pop(array) == &a[0]);
    test_assert(array_length(array) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_pop_from_empty(void)
{
    Array *array = array_create();
    test_assert(array_length(array) == 0);
    test_assert((int*) array_pop(array) == NULL);
    test_assert(array_length(array) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_pop_from_null(void)
{
    test_assert(array_pop(NULL) == NULL);
    
    return TEST_PASS;
}

static int test_array_get(void)
{
    int a[] = {1, 2};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    test_assert((int*) array_get(array, 0) == &a[0]);
    test_assert((int*) array_get(array, 1) == &a[1]);
    array_free(array);

    return TEST_PASS;
}

static int test_array_get_out_of_bounds(void)
{
    int a[] = {1, 2};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    test_assert((int*) array_get(array, -1) == NULL);
    test_assert((int*) array_get(array, 2) == NULL);
    array_free(array);

    return TEST_PASS;
}

static int test_array_get_from_empty(void)
{
    Array *array = array_create();
    test_assert(array_get(array, -1) == NULL);
    test_assert(array_get(array, 0) == NULL);
    test_assert(array_get(array, 1) == NULL);
    array_free(array);

    return TEST_PASS;
}

static int test_array_get_from_null(void)
{
    test_assert(array_get(NULL, -1) == NULL);
    test_assert(array_get(NULL, 0) == NULL);
    test_assert(array_get(NULL, 1) == NULL);

    return TEST_PASS;
}

static int test_array_set(void)
{
    int a[] = {1, 2};
    Array *array = array_create();
    array_push(array, &a[0]);
    test_assert(array_get(array, 0) == &a[0]);
    test_assert(array_set(array, 0, &a[1]) == 1);
    test_assert(array_get(array, 0) == &a[1]);

    return TEST_PASS;
}

static int test_array_set_out_of_bounds(void)
{
    Array *array = array_create();
    test_assert(array_set(array, -1, NULL) == 0);
    test_assert(array_set(array, 1, NULL) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_set_in_empty(void)
{
    Array *array = array_create();
    test_assert(array_set(array, 0, NULL) == 0);
    array_free(array);

    return TEST_PASS;
}

static int test_array_set_in_null(void)
{
    test_assert(array_set(NULL, 0, NULL) == 0);

    return TEST_PASS;
}

static int test_array_last(void)
{
    int a[] = {1, 2};
    Array *array = array_create();
    array_push(array, &a[0]);
    test_assert((int*) array_last(array) == &a[0]);
    array_push(array, &a[1]);
    test_assert((int*) array_last(array) == &a[1]);
    array_free(array);

    return TEST_PASS;
}

static int test_array_last_of_empty(void)
{
    Array *array = array_create();
    test_assert((int*) array_last(array) == NULL);
    array_free(array);

    return TEST_PASS;
}

static int test_array_last_of_null(void)
{
    test_assert(array_last(NULL) == NULL);

    return TEST_PASS;
}

static int test_array_sort(void)
{
    int a[] = {8, 3, 25, 87, 2, 17, 5, 9, 16};
    Array *array = array_create();
    array_push(array, &a[0]); /*  8 */
    array_push(array, &a[1]); /*  3 */
    array_push(array, &a[2]); /* 25 */
    array_push(array, &a[3]); /* 87 */
    array_push(array, &a[4]); /*  2 */
    array_push(array, &a[5]); /* 17 */
    array_push(array, &a[6]); /*  5 */
    array_push(array, &a[7]); /*  9 */
    array_push(array, &a[8]); /* 16 */
    array_sort(array, compare);
    test_assert(array_get(array, 0) == &a[4]);
    test_assert(array_get(array, 1) == &a[1]);
    test_assert(array_get(array, 2) == &a[6]);
    test_assert(array_get(array, 3) == &a[0]);
    test_assert(array_get(array, 4) == &a[7]);
    test_assert(array_get(array, 5) == &a[8]);
    test_assert(array_get(array, 6) == &a[5]);
    test_assert(array_get(array, 7) == &a[2]);
    test_assert(array_get(array, 8) == &a[3]);

    return TEST_PASS;
}

static int test_array_sort_empty(void)
{
    Array *array = array_create();
    array_sort(array, compare);
    array_free(array);

    return TEST_PASS;
}

static int test_array_sort_null(void)
{
    int a[] = {1, 2};
    Array *array = array_create();
    array_push(array, &a[0]);
    array_push(array, &a[1]);
    array_sort(NULL, compare);
    array_sort(array, NULL);
    array_sort(NULL, NULL);
    array_free(array);

    return TEST_PASS;
}

int main(void)
{
    test_run(test_array_create);
    test_run(test_array_create_no_memory);
    test_run(test_array_create_no_memory_for_elements);
    test_run(test_array_length_of_empty);
    test_run(test_array_length_of_null);
    test_run(test_array_insert_at_beginning);
    test_run(test_array_insert_at_middle);
    test_run(test_array_insert_at_end);
    test_run(test_array_insert_adds_null);
    test_run(test_array_insert_out_of_bounds);
    test_run(test_array_insert_increases_length);
    test_run(test_array_insert_to_null);
    test_run(test_array_remove_from_beginning);
    test_run(test_array_remove_from_middle);
    test_run(test_array_remove_from_end);
    test_run(test_array_remove_out_of_bounds);
    test_run(test_array_remove_decreases_length);
    test_run(test_array_remove_from_null);
    test_run(test_array_push_adds_to_end);
    test_run(test_array_push_adds_null);
    test_run(test_array_push_increases_length);
    test_run(test_array_push_to_null);
    test_run(test_array_capacity_increases);
    test_run(test_array_capacity_no_memory);
    test_run(test_array_capacity_of_empty);
    test_run(test_array_capacity_of_null);
    test_run(test_array_pop_returns_element);
    test_run(test_array_pop_from_empty);
    test_run(test_array_pop_from_null);
    test_run(test_array_get);
    test_run(test_array_get_out_of_bounds);
    test_run(test_array_get_from_empty);
    test_run(test_array_get_from_null);
    test_run(test_array_set);
    test_run(test_array_set_out_of_bounds);
    test_run(test_array_set_in_empty);
    test_run(test_array_set_in_null);
    test_run(test_array_last);
    test_run(test_array_last_of_empty);
    test_run(test_array_last_of_null);
    test_run(test_array_sort);
    test_run(test_array_sort_empty);
    test_run(test_array_sort_null);
    test_print_stats();

    return test_get_fail_count();
}
