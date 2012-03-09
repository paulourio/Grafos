#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <cassert>

using namespace std;

#define foreach(t,i,c)	for (t::iterator i = c.begin();  i != c.end();  i++)

enum colors {WHITE=1, GRAY, BLACK};

typedef struct node {
	int color, time, value;
	list<int> adj;
} node;

typedef vector<struct node> Graph;

Graph graph;
int TTL, ncase = 1;
queue<int> Q;
#define enqueue(v)	Q.push(v)
#define dequeue()	Q.front(); Q.pop()
#define clear_queue()	while (!Q.empty()) Q.pop()

static node *get_graph_node(const int avalue)
{
	foreach(Graph, it, graph)
		if (it->value == avalue)
			return &(*it);
	node n;
	n.value = avalue;
	graph.push_back(n);
	return &graph.back();
}

static void initialize_graph(const int S)
{
	foreach(Graph, it, graph) {
		it->color = it->value == S?  GRAY:  WHITE;
		if (it->value == S)
			it->time = 0;
	}
	clear_queue();
}

static int count_white_nodes(void)
{
	int total = 0;
	foreach(Graph, it, graph)
		if (it->color == WHITE)
			total++;
	return total;
}

static void process_adjacents(node *n)
{
	foreach(list<int>, it, n->adj) {
		node *adj = get_graph_node(*it);
		if (adj->color == WHITE) {
			adj->time = n->time + 1;
			adj->color = GRAY;
			if (adj->time < TTL)
				enqueue(adj->value);
		}
	}
}

static void process_next_edge(void)
{
	int current = dequeue();
	node *ncurr = get_graph_node(current);
	if (ncurr->time < TTL)
		process_adjacents(ncurr);
	ncurr->color = BLACK;
}

static int run_bfs(const int S)
{
	initialize_graph(S);
	enqueue(S);
	while (!Q.empty())
		process_next_edge();
	return count_white_nodes();
}

static void BFS(void)
{
	int S;

	while (scanf("%u %u", &S, &TTL) == 2 && !(S == 0))
		printf("Case %u: %u nodes not reachable from node %u with TTL = %u.\n",
				ncase++, run_bfs(S), S, TTL);
}

static void add_edge(const int from, const int to)
{
	get_graph_node(from)->adj.push_back(to);
}

static void read_edge(void)
{
	int from, to;

	if (scanf("%u %u", &from, &to) == 2) {
		add_edge(from, to);
		add_edge(to, from);
	}
}

int main(void)
{
	int NC;

	while (scanf("%d", &NC) == 1 && NC != 0) {
		while (NC--)
			read_edge();
		BFS();
		graph.clear();
	}
	return EXIT_SUCCESS;
}
