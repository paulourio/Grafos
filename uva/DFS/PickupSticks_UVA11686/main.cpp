#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <map>
#include <list>
#include <vector>
#include <queue>

using namespace std;

#define foreach(i,l)  for(typeof((l).begin()) i=(l).begin(); i!=(l).end(); i++)

#ifndef ONLINE_JUDGE
#define err(...)	printf(__VA_ARGS__)
#else
#define err(...)
#endif

enum {WHITE, GRAY, BLACK};
struct gnode {
	int color;
	list<long int> adj;
};

typedef map<long int, gnode *>  Graph;
typedef list<long int> Queue;

long int N, M;
Graph graph;
Queue Q;

static void add_adjacent(long int &a, long int &b)
{
	if (graph[a] == NULL) {
		graph[a] = new gnode;
		graph[a]->color = WHITE;
	}
	if (graph[b] == NULL) {
		graph[b] = new gnode;
		graph[b]->color = WHITE;
	}
	graph[a]->adj.push_back(b);
}

static void read_sticks(long int &M)
{
	long int a, b;
	while (M--)
		if (scanf("%li %li", &a, &b) == 2)
			add_adjacent(b, a);
}

static void free_graph(void)
{
	foreach(n, graph)
		delete (*n).second;
	graph.clear();
	Q.clear();
}

static void show_order(void)
{
	while (!Q.empty()) {
		printf("%li\n", Q.front());
		Q.pop_front();
	}
}

bool stop;
static void DFS_Visit(long int v, gnode *node)
{
	err("DFS_VISIT %li\n", v);
	node->color = GRAY;
	foreach(a, node->adj) {
		gnode *adj = graph[*a];
		if (adj->color == WHITE) {
			DFS_Visit(*a, adj);
		} else if (adj->color == GRAY) {
			puts("IMPOSSIBLE");
			stop = true;
		}
		if (stop)
			return;
	}
	node->color = BLACK;
	Q.push_back(v);
}

static void topological_sort(void)
{
	stop = false;
	foreach(n, graph) {
		if (n->second->color == WHITE)
			DFS_Visit(n->first, n->second);
		if (stop)
			return;
	}
	show_order();
}

int main(void)
{
	while (scanf("%li %li", &N, &M) == 2) {
		if (N == 0 && M == 0)
			break;
		read_sticks(M);
		topological_sort();
		free_graph();
	}
	return 0;
}
