/*
 * test.c
 *
 * License: FreeBSD
 */
#include <stdio.h>
#include <stdlib.h>
#include <list.h>

int main(int argc, char *argv[])
{
	list l = NULL;

	if (argc < 3) {
		fprintf(stderr, "test_list [fbs] [values]\n");
		exit(EXIT_FAILURE);
	}

	char where = *(argv[1]);

	argc--; argv++;
	while (--argc)
		switch (where) {
		case 'f': list_insert_front(&l, atoi(*++argv)); break;
		case 'b': list_insert_back(&l, atoi(*++argv)); break;
		case 's': list_insert_sorted(&l, atoi(*++argv)); break;
		default: fprintf(stderr, "FAIL: %c\n", where); exit(EXIT_FAILURE);
	}
	list_test(&l);
	list_print(&l);
	list_clear(&l);
	return EXIT_SUCCESS;
}
