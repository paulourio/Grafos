/*
 * isempty.c
 *
 * License: FreeBSD
 */
#include <list.h>
#include <assert.h>
#include <stdbool.h>
#include "list_test.h"

void test_isempty()
{
	list l = NULL;

	assert(list_isempty(&l) == true);
	list_fill(&l, 40);
	list_print(&l, print_int_node);
	assert(list_isempty(&l) == false);
	list_clear(&l, NULL);
	assert(list_isempty(&l) == true);
	assert(l == NULL);
}


void test_list_count()
{
	list l = NULL;

	list_fill(&l, 40);
	assert(list_count(&l) == 40);
	list_clear(&l, NULL);
	assert(l == NULL);
}

static bool is_pair(const void *value)
{
	int iv = *(int *)value;

	return iv != 0 && !(iv % 2);
}

static void test_list_delete_if(void)
{
	list l = NULL;

	list_fill(&l, 40);
	list_delete_if(&l, is_pair, NULL);
	assert(list_count(&l) == 20);
	list_clear(&l, NULL);
	assert(l == NULL);
}

void test_list_count_if()
{
	list l = NULL;

	list_fill(&l, 40);
	assert(list_count_if(&l, is_pair) == 20);
	list_clear(&l, NULL);
	assert(l == NULL);
	test_list_delete_if();
}
