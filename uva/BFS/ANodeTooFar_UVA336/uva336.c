#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

enum colors {WHITE=1, GRAY, BLACK};

typedef struct list {
	unsigned int value;
	struct list *next;
} list;

typedef struct {
	int color;
	int time;
	unsigned int value;
	list *adjlist; /* linked list */
} node;

#define GRAPH_SIZE 30
node graph[GRAPH_SIZE];

unsigned int ncase = 1;

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
	graph[i].value = node_value;
	return i;
}

static void initialize_graph(const unsigned int S)
{
	int i;

	for (i = 0; i < GRAPH_SIZE; i++) {
		graph[i].color = graph[i].value == S? GRAY: WHITE;
		if (graph[i].value == S)
			graph[i].time = 0;
	}
}

static void find_out_edges(const unsigned int TTL)
{
	unsigned int current = dequeue();
	unsigned int icurr = get_index(current);
	list *adj = graph[icurr].adjlist;
	while (adj != NULL) {
		unsigned int iadj = get_index(adj->value);
		if (graph[iadj].color == WHITE) {
			graph[iadj].color = GRAY;
			graph[iadj].time = graph[icurr].time + 1;
			if (graph[iadj].time < TTL)
				enqueue(adj->value);
		}
		adj = adj->next;
	}
	graph[icurr].color = BLACK;
}

static unsigned int count_white_nodes(void)
{
	unsigned int i, total = 0;
	for (i = 0; i < GRAPH_SIZE; i++)
		if (graph[i].value > 0 && graph[i].color == WHITE)
			total++;
	return total;
}

static unsigned int run_bfs(const unsigned int S, const unsigned int TTL)
{
	initialize_graph(S);
	enqueue(S);
	while (Q != NULL)
		find_out_edges(TTL);
	return count_white_nodes();
}

static void BFS(void)
{
	unsigned int S, TTL, total;

	while (scanf("%u %u", &S, &TTL) == 2 && S != 0 && TTL != 0) {
		total = run_bfs(S, TTL);
		printf("Case %u: %u nodes not reachable from node %u with TTL = %u.\n",
				ncase++, total, S, TTL);
	}
}

/*==============================================*/

static void add_edge(const unsigned int from, const unsigned int to)
{
	unsigned int ifrom = get_index(from);

	list *n = malloc(sizeof(list));
	assert(n != NULL);
	n->next = graph[ifrom].adjlist;
	graph[ifrom].adjlist = n;
	n->value = to;
}

static void read_edge(void)
{
	unsigned int from, to;

	if (scanf("%u %u", &from, &to) == 2) {
		add_edge(from, to);
		add_edge(to, from);
	}
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
	int NC;
	
	while ((scanf("%d", &NC) == 1) && NC != 0) {
		memset(graph, 0, GRAPH_SIZE * sizeof(node));
		while (NC--)
			read_edge();
		BFS();
		free_all();
	}
	return EXIT_SUCCESS;
}
