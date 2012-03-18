#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <map>
#include <list>
#include <vector>
#include <queue>

using namespace std;

#define MAX		30
enum {FULL_OF_ROCK = '#', EMPTY = '.', START = 'S', EXIT = 'E'};
enum {WHITE, GRAY, BLACK};

#define foreach(i,l)  for(typeof((l).begin()) i=(l).begin(); i!=(l).end(); i++)

#ifndef ONLINE_JUDGE
#define err(...)	printf(__VA_ARGS__)
#else
#define err(...)
#endif

union cell {
	unsigned long int value;
	struct {
		unsigned int level: 6;
		unsigned int row: 6;
		unsigned int col: 6;
	};
};

unsigned int levels, rows, cols;
bool FOUND;
cell start;
char dungeon[MAX][MAX][MAX];

#define CELL(_cell)	(dungeon[_cell.level][_cell.row][_cell.col])

struct gnode {
	cell value;
	int color, time;
	list<unsigned int> adj;
};

typedef queue<unsigned int> Queue;
typedef map<unsigned int, gnode *> Graph;
Graph graph;
Queue Q;

static gnode *get_node(unsigned int value)
{
	if (graph[value] == NULL) {
		graph[value] = new gnode;
		graph[value]->color = WHITE;
		graph[value]->value.value = value;
	}
	return graph[value];
}

static void print_dungeon(void)
{
	unsigned int L, R, C;
	for (L = 0;  L<levels;  L++) {
		for (R = 0;  R<rows;  R++) {
			for (C = 0;  C<cols;  C++)
				err("%c", dungeon[L][R][C]);
			err("\n");
		}
		err("\n");
	}
}

static void add_adjacent(gnode *parent, cell &adj)
{
	gnode *n = get_node(adj.value);
	if (n->color != WHITE)
		return;
	parent->adj.push_back(adj.value);
	n->time = parent->time + 1;
	n->color = GRAY;
	Q.push(adj.value);
}

#define valid_cell(c) \
		((0 <= c.col && c.col < cols && \
		0 <= c.row && c.row < rows && \
		0 <= c.level && c.level < levels) \
		&& CELL(c) != FULL_OF_ROCK)

static void generate_cells(unsigned int c)
{
	gnode *node = get_node(c);
	cell &value = node->value;

	#define DELTAS 	6
	unsigned int deltax[DELTAS] = { 0, +1,  0, -1,  0,  0};
	unsigned int deltay[DELTAS] = {+1,  0, -1,  0,  0,  0};
	unsigned int deltaz[DELTAS] = { 0,  0,  0,  0, -1, +1};

	for (int i = 0;  i < DELTAS;  i++) {
		cell n;
		n.col = value.col + deltax[i];
		n.row = value.row + deltay[i];
		n.level = value.level + deltaz[i];
		if (valid_cell(n)) {
			if (CELL(n) == EXIT) {
				printf("Escaped in %d minute(s).\n", node->time + 1);
				FOUND = true;
				return;
			}
			add_adjacent(node, n);
		}
	}
	node->color = BLACK;
}

static void bfs_next(void)
{
	unsigned int v = Q.front();
	Q.pop();

	err("Working on [%u][%u][%u]\n", graph[v]->value.level,
			graph[v]->value.row, graph[v]->value.col);
	generate_cells(v);
}

static void BFS(void)
{
	foreach(v, graph)
		delete v->second;
	graph.clear();
	while (!Q.empty())
		Q.pop();
	gnode *g = get_node(start.value);
	g->color = GRAY;
	g->time = 0;
	Q.push(start.value);
	FOUND = false;
	while (!Q.empty() && !FOUND)
		bfs_next();
	if (!FOUND)
		puts("Trapped!");
}

static void read_cell(unsigned int L, unsigned int R, unsigned int C)
{
	dungeon[L][R][C] = (char) getchar();
	assert(dungeon[L][R][C] != '\n');
	err("Reading into [%u][%u][%u]\n", L, R, C);
	if (dungeon[L][R][C] == START) {
		start.level = L;
		start.row = R;
		start.col = C;
		err("Start found at [%u][%u][%u]\n", start.level,
				start.row, start.col);
	}
}

int main(void)
{
	unsigned int L, R, C; /* counters */

	while (scanf("%u %u %u", &levels, &rows, &cols) == 3) {
		if (levels == 0 && rows == 0 && cols == 0)
			exit(0);
		(void) getchar();
		memset(dungeon, 0, sizeof(dungeon));
		for (L = 0;  L<levels;  L++) {
			for (R = 0;  R<rows;  R++) {
				for (C = 0;  C < cols;  C++)
					read_cell(L, R, C);
				(void) getchar();
			}
			(void) getchar();
		}
		print_dungeon();
		err("Solving...\n");
		BFS();
	}
	return 0;
}
