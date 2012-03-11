#include <cstdio>
#include <cstdlib>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef ONLINE_JUDGE
#define err(...)	printf(__VA_ARGS__)
#else
#define err(...)
#endif

#define foreach(t,i,v)	for (t::iterator i = v.begin();  i != v.end();  i++)

enum colors {WHITE=1, GRAY, BLACK};

#define LETTER(n)	(n >> 8)
#define NUMBER(n)	(n & 0xFF)
#define PACK(l,n)	((l << 8) | n)
#define UNPACK(v)	LETTER(v), NUMBER(v)

typedef struct gnode {
	int value, color, time;
	list<int> adj;
} gnode;
typedef vector<gnode> Graph;

Graph graph;
queue<int> Q;
int from, to;
#define enqueue(v)	Q.push(v)
static inline int dequeue() { int r = Q.front(); Q.pop(); return r; }
int TOTAL_MOVES;
#define found		(TOTAL_MOVES > 0)

static gnode &get_graph_node(int value)
{
	foreach(Graph, it, graph)
		if (it->value == value)
			return *it;
	gnode *nnode = new gnode;
	nnode->color = WHITE;
	nnode->time = 0;
	nnode->value = value;
	graph.push_back(*nnode);
	return graph.back();
}

static void initialize_graph(int S)
{
	TOTAL_MOVES = 0;
	while (!Q.empty())
		Q.pop();
	graph.clear();
	get_graph_node(S).color = GRAY; /* Add node S into graph */
}

static void add_edge(gnode &from, int letter, int number)
{
	gnode& edge = get_graph_node(PACK(letter, number));

	if (edge.color != WHITE)
		return;
	edge.time = from.time + 1;
	err("\tAdding %c%c (%d) -> %c%c (%d) -- time %d\n", UNPACK(from.value),
			from.value, UNPACK(edge.value),
			edge.value, edge.time);
	from.adj.push_back(edge.value);
	enqueue(edge.value);
	if (edge.value == to)
		TOTAL_MOVES = edge.time;
}

#define letter_in_board(v)	('a' <= v && v < 'h')
#define number_in_board(v)	('1' <= v && v < '8')
static void generate_square_edges(gnode &n)
{
	int deltax[8] = {-2, -2, -1, -1, +1, +1, +2, +2};
	int deltay[8] = {-1, +1, -2, +2, -2, +2, -1, +1};

	for (int i = 0;  !found && i < 8;  i++) {
		int X = LETTER(n.value) + deltax[i];
		int Y = NUMBER(n.value) + deltay[i];
		if (letter_in_board(X) && number_in_board(Y))
			add_edge(n, X, Y);
	}
}

static void BFS_next_edge(void)
{
	gnode& gcurr = get_graph_node(dequeue());

	err("Working on %c%c (%d) time: %d\n", UNPACK(gcurr.value), gcurr.value, gcurr.time);
	generate_square_edges(gcurr);
	gcurr.color = BLACK;
}

static int BFS(void)
{
	initialize_graph(from);
	enqueue(from);
	while (!Q.empty() && !found)
		BFS_next_edge();
	return TOTAL_MOVES;
}

int main(void)
{
	char F1, F2, T1, T2;
	while (scanf("%c%c %c%c", &F1, &F2, &T1, &T2) == 4) {
		(void) getchar();
		from = PACK(F1, F2);
		to = PACK(T1, T2);

		int total = (from != to?  BFS():  0);
		printf("To get from %c%c to %c%c takes %u knight moves.\n",
			UNPACK(from), UNPACK(to), total);
	}
	return 0;
}
