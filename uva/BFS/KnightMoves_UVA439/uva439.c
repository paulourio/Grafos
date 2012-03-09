#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

/* Get the letter (x position) */
#define LETTER(pos)	(pos >> 8)
/* Get the number (y position) */
#define NUMBER(pos)	(pos & 0xFF)
/* Expand the position to printf arguments */
#define EXPAND(pos)	LETTER(pos)+'a', NUMBER(pos)+'1'
/* Create a node value */
#define SQUARE(letter, number)	(((letter) << 8) | (number))

#ifndef ONLINE_JUDGE
#define err(...)	printf(__VA_ARGS__)
#else
#define err(...)
#endif

enum colors {WHITE=1, GRAY, BLACK};

typedef struct list {
	uint16_t value;
	struct list *next;
} list;

typedef struct {
	int color;
	int time;
	uint16_t value;
	list *adjlist; /* linked list */
} node; /* graph node (NOT a linked list node) */

#define GRAPH_SIZE 64
node graph[GRAPH_SIZE];

uint16_t from, to; /* initial and final square */
int TOTAL_MOVES;

static void free_list(list *l)
{
	while (l != NULL) {
		list *next = l->next;
		free(l);
		l = next;
	}
}
/* =========== QUEUE ============= */
typedef list queue;
queue *Q = NULL;
static void enqueue(unsigned int value)
{
	queue *q = malloc(sizeof(queue)), *l = Q;
	assert(q != NULL);
	q->value = value;
	if (Q == NULL) {
		Q = q;
	} else {
		while (l != NULL && l->next != NULL)
			l = l->next;
		l->next = q;
	}
	q->next = NULL;
}

static unsigned int dequeue(void)
{
	assert(Q != NULL);
	unsigned int value = Q->value;
	queue *q = Q;
	Q = Q->next;
	free(q);
	return value;
}

/* ========= END QUEUE =========== */
/* Find a graph node, or create at the first available position */
static unsigned int get_index(const unsigned int node_value)
{
	unsigned int i = 0;

	while (i < GRAPH_SIZE && graph[i].value != 0 && graph[i].value != node_value)
		i++;
	assert(i < GRAPH_SIZE);
	if (graph[i].value == 0) {
		graph[i].value = node_value;
		graph[i].color = WHITE;
	}
	return i;
}

static void initialize_graph(const unsigned int S)
{
	int i;

	(void) get_index(S);
	TOTAL_MOVES = 0;
	for (i = 0; i < GRAPH_SIZE; i++) {
		graph[i].color = graph[i].value == S? GRAY: WHITE;
		if (graph[i].value == S)
			graph[i].time = 0;
	}
}

static void add_edge(const unsigned int from, const unsigned int to)
{
	unsigned int ifrom = get_index(from);

	list *n = malloc(sizeof(list));
	assert(n != NULL);
	n->next = graph[ifrom].adjlist;
	graph[ifrom].adjlist = n;
	n->value = to;

}

#define in_board(v)	(0 <= v && v < 8)
static void add_square_edges(const unsigned int s)
{
	int i, deltax[] = {-1, +1, +2, +2, -1, +1, -2, -2};
	int    deltay[] = {+2, +2, -1, +1, -2, -2, -1, +1};

	for (i = 0;  i < sizeof(deltax)/sizeof(int);  i++) {
		int X = LETTER(s) + deltax[i],  Y = NUMBER(s) + deltay[i];

		if (in_board(X) && in_board(Y))
			add_edge(s, SQUARE(X, Y));
	}
}

static void find_out_edges(void)
{
	unsigned int current = dequeue();
	unsigned int icurr = get_index(current);

	add_square_edges(current);

	list *adj = graph[icurr].adjlist;
	while (adj != NULL) {
		unsigned int iadj = get_index(adj->value);
		if (graph[iadj].color == WHITE) {
			graph[iadj].color = GRAY;
			graph[iadj].time = graph[icurr].time + 1;
			if (adj->value == to) {
				TOTAL_MOVES = graph[iadj].time;
				return;
			}
			enqueue(adj->value);
		}
		adj = adj->next;
	}
	graph[icurr].color = BLACK;
}

static unsigned int run_bfs(void)
{
	initialize_graph(from);
	enqueue(from);
	while (Q != NULL)
		find_out_edges();
	return TOTAL_MOVES;
}

static void BFS(void)
{
	unsigned int total;

	total = (from != to?  run_bfs():  0);
	printf("To get from %c%c to %c%c takes %u knight moves.\n",
		EXPAND(from), EXPAND(to), total);
}

static void free_all(void)
{
	int i;
	for (i = 0; i < GRAPH_SIZE; i++)
		if (graph[i].adjlist != NULL)
			free_list(graph[i].adjlist);
}

int main(void)
{
	char La, Na, Lb, Nb;
	
	while (scanf("%c%c %c%c", &La, &Na, &Lb, &Nb) == 4) {
		(void) getchar();
		from = SQUARE(La - 'a', Na - '1');
		to = SQUARE(Lb - 'a', Nb - '1');

		memset(graph, 0, GRAPH_SIZE * sizeof(node));
		BFS();
		free_all();
	}
	return EXIT_SUCCESS;
}
