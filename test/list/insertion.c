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

static bool fake_free_value(const void *value)
{
	/* Empty.  To be used when values are local variables. */
	return value == NULL;
}

void test_insert_front() {
	list l = NULL, tmp;
	int values[] = {1, 2, 3, 4, 5};
	int result[] = {5, 4, 3, 2, 1};
	unsigned int i;

	for (i=0; i<length(values); i++) {
		list_insert_front(&l, &values[i]);
		assert(*list_get(&l, 0) == &values[i]);
	}
	tmp = l;
	i = 0;
	while (tmp != NULL) {
		assert(*(int *)tmp->value == result[i]);
		i++;
		tmp = tmp->next;
	}
	assert(i == length(result));
	list_clear(&l, fake_free_value);
	assert(l == NULL);
}
