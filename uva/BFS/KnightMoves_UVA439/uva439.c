#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define LETTER(pos)	(pos >> 8)
#define NUMBER(pos)	(pos & 0xFF)
#define EXPAND(pos)	LETTER(pos)+'a', NUMBER(pos)+'1'
#define SQUARE(letter, number)	((letter << 8) + number)

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
} node;

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

	/*err("Adding %c%c ->  %c%c\n", EXPAND(from), EXPAND(to));*/

	list *n = malloc(sizeof(list));
	assert(n != NULL);
	n->next = graph[ifrom].adjlist;
	graph[ifrom].adjlist = n;
	n->value = to;

}

static void add_square_edges(const unsigned int s)
{
	if (LETTER(s) > 0 && NUMBER(s) < 6)
		add_edge(s, SQUARE(LETTER(s) - 1, NUMBER(s) + 2));
	if (LETTER(s) < 7 && NUMBER(s) < 6)
		add_edge(s, SQUARE(LETTER(s) + 1, NUMBER(s) + 2));

	if (LETTER(s) < 6 && NUMBER(s) > 0)
		add_edge(s, SQUARE(LETTER(s) + 2, NUMBER(s) - 1));
	if (LETTER(s) < 6 && NUMBER(s) < 7)
		add_edge(s, SQUARE(LETTER(s) + 2, NUMBER(s) + 1));

	if (LETTER(s) > 0 && NUMBER(s) > 1)
		add_edge(s, SQUARE(LETTER(s) - 1, NUMBER(s) - 2));
	if (LETTER(s) < 7 && NUMBER(s) > 1)
		add_edge(s, SQUARE(LETTER(s) + 1, NUMBER(s) - 2));

	if (LETTER(s) > 1 && NUMBER(s) > 0)
		add_edge(s, SQUARE(LETTER(s) - 2, NUMBER(s) - 1));
	if (LETTER(s) > 1 && NUMBER(s) < 7)
		add_edge(s, SQUARE(LETTER(s) - 2, NUMBER(s) + 1));
}

static void find_out_edges(void)
{
	unsigned int current = dequeue();
	unsigned int icurr = get_index(current);

	add_square_edges(current);

	list *adj = graph[icurr].adjlist;
	while (adj != NULL) {
		unsigned int iadj = get_index(adj->value);
		/*err("Running with %c%c\n", EXPAND(adj->value));*/
		if (graph[iadj].color == WHITE) {
			graph[iadj].color = GRAY;
			graph[iadj].time = graph[icurr].time + 1;
			/*err("Running with %c%c painted in GRAY with time %d\n", EXPAND(adj->value), graph[iadj].time);*/
			if (adj->value == to) {
				TOTAL_MOVES = graph[iadj].time;
				while (Q != NULL)
					(void) dequeue();
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

	if (from != to)
		total = run_bfs();
	else
		total = 0;
	printf("To get from %c%c to %c%c takes %u knight moves.\n",
		EXPAND(from), EXPAND(to), total);
}

/*==============================================*/

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
		from = ((La - 'a') << 8) + (Na - '1');
		to = ((Lb - 'a') << 8) + (Nb - '1');

		memset(graph, 0, GRAPH_SIZE * sizeof(node));
		BFS();
		free_all();
	}
	return EXIT_SUCCESS;
}
