/*
 * list_test.h
 *
 * License: FreeBSD
 */

#ifndef _LIST_TEST_H_
#define _LIST_TEST_H_

#include <stdio.h>

#define err(...)	fprintf(stderr, __VA_ARGS__ "\n")

/* insertion.c */
void test_insert_front(void);

#endif /* _LIST_TEST_H_ */
