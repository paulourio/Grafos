#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <list>
#include <deque>

#define MAX		30
#define FULL_OF_ROCK	'#'
#define EMPTY		'.'
#define START		'S'
#define EXIT		'E'

#ifndef ONLINE_JUDGE
#define err(...)	printf(__VA_ARGS__)
#else
#define err(...)
#endif

int levels, rows, columns;
char dungeon[MAX][MAX][MAX];

static void print_dungeon(void)
{
	int L, R, C;
	for (L = 0;  L<levels;  L++) {
		for (R = 0;  R<rows;  R++)
			err("%s\n", dungeon[L][R]);
		err("\n");
	}
}

int main(void)
{
	int L, R, C; /* counters */

	while (scanf("%d %d %d", &levels, &rows, &columns) == 3) {
		if (levels == 0 && rows == 0 && columns == 0)
			exit(0);
		memset(dungeon, 0, sizeof(dungeon));
		for (L = 0;  L<levels;  L++) {
			for (R = 0;  R<rows;  R++)
				assert(scanf("%s", dungeon[L][R]) == 1);
			/* Watch out! NDEBUG must not be defined. */
			assert(getchar() == '\n');
		}
		print_dungeon();
	}
	return 0;
}
