/*
 * list_test.h
 *
 * License: FreeBSD
 */

#ifndef _LIST_TEST_H_
#define _LIST_TEST_H_

#include <stdio.h>
#include <stdbool.h>
#include <features.h>

#ifdef __GNUC__
#define __unused	__attribute__((unused))
#else
#define __unused
#endif

#define err(...)	fprintf(stderr, __VA_ARGS__ "\n")

/* insertion.c */
void test_insert_front(void);
void test_insert_back(void);
void test_insert_sorted(void);

/* general.c */
void test_isempty(void);
void test_list_count(void);
void test_list_count_if(void);

__unused
static bool fake_free_value(const void *value)
{
	/* Empty.  To be used when values are local variables. */
	return value == NULL;
}

__unused
static int compare_int_node(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

__unused
static void print_int_node(const void *n, const int first)
{
	if (first)
		printf(", ");
	printf("%i", * (int *) n);
}

#endif /* _LIST_TEST_H_ */
