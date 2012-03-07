/*
 * remove.c
 *
 * License: FreeBSD
 */
#include <list.h>
#include <assert.h>

void test_list_delete_if()
{
	list l = NULL;

	list_fill(&l, 20);


	list_clear(&l, NULL);
	assert(l == NULL);
}

