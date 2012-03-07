/*
 * insertion.c
 *
 * License: FreeBSD
 */
#include <list.h>
#include <assert.h>
#include <stdbool.h>
#include "list_test.h"

#define length(array)	(sizeof(array)/sizeof(int))

#define INSERT_FRONT 0
#define INSERT_BACK 1
#define INSERT_SORTED 2
static void test_insertion(int input[], int expected[], size_t size,
		unsigned int type)
{
	list l = NULL, tmp;
	unsigned int i;

	for (i=0; i<size; i++) {
		switch (type) {
		default:
		case INSERT_FRONT:
			list_insert_front(&l, &input[i]);
			assert(*list_get(&l, 0) == &input[i]);
			break;
		case INSERT_BACK:
			list_insert_back(&l, &input[i]);
			assert(list_get_back_node(&l)->value == &input[i]);
			break;
		case INSERT_SORTED:
			list_insert_sorted(&l, &input[i], compare_int_node);
			list_sorted(&l, compare_int_node);
			break;
		}
	}
	list_print(&l, print_int_node);
	puts("");
	tmp = l;
	i = 0;
	while (tmp != NULL) {
		assert(*(int *)tmp->value == expected[i]);
		i++;
		tmp = tmp->next;
	}
	assert(i == size);
	list_clear(&l, fake_free_value);
	assert(l == NULL);
}


void test_insert_front()
{
	int values[] = {1, 2, 3, 4, 5};
	int result[] = {5, 4, 3, 2, 1};
	test_insertion(values, result, length(values), INSERT_FRONT);
}


void test_insert_back()
{
	int values[] = {1, 2, 3, 4, 5};
	int result[] = {1, 2, 3, 4, 5};
	test_insertion(values, result, length(values), INSERT_BACK);
}

void test_insert_sorted()
{
	int values[] = {-80, -91, 40, 0, 1, 2, 87, 0, 3};
	int result[] = {-91, -80, 0, 0, 1, 2, 3, 40, 87};
	test_insertion(values, result, length(values), INSERT_SORTED);
}
