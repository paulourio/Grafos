/*
 * test.c
 *
 * License: FreeBSD
 */
#include <stdio.h>
#include <stdlib.h>
#include <list.h>

static int compare_int(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

static void print_int(const void *v, const int first)
{
	if (first)
		printf(", ");
	printf("%d", *(int*)v);
}

int main(int argc, char *argv[])
{
	list l = NULL;

	if (argc < 3) {
		fprintf(stderr, "test_list [fbs] [values]\n");
		exit(EXIT_FAILURE);
	}

	char where = *(argv[1]);

	argc--; argv++;
	while (--argc) {
		int *value = malloc(sizeof(int));
		*value = atoi(*++argv);
		switch (where) {
		case 'f': list_insert_front(&l, value); break;
		case 'b': list_insert_back(&l, value); break;
		case 's': list_insert_sorted(&l, value, compare_int); break;
		default: fprintf(stderr, "FAIL: %c\n", where); exit(EXIT_FAILURE);
		}
	}
	list_print(&l, print_int);
	list_clear(&l, NULL);
	return EXIT_SUCCESS;
}
