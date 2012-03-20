#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <map>
#include <list>
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
	int color, time;
	list<int> adj;
};

typedef map<int, gnode *>  Graph;
typedef list<int> Queue;

Graph graph;
Queue Q;
char buffer[301];

static gnode *get_node(int v)
{
	gnode *node = graph[v];
	if (node == NULL) {
		node = new gnode;
		node->color = WHITE;
		node->time = 1;
		graph[v] = node;
	}
	return graph[v];
}

static void add_adjacent(int a, int b)
{
	(void) get_node(b);
	get_node(a)->adj.push_back(b);
}

#define gc()	(void) getchar()
static void read_inequalities(void)
{
	char ca, cb;
	int I;
	scanf("%d", &I), gc();
	err("\tI: %d\n", I);
	while (I--) {
		scanf("%c>%c", &ca, &cb), gc();
		err("\tAdding %c > %c\n", ca, cb);
		add_adjacent(int(cb), int(ca));
	}
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
	err("Topological result:\n");
	while (!Q.empty()) {
		err("\t%c (Value: %d)\n", Q.front(), graph[Q.front()]->time);
		Q.pop_front();
	}
}

static void DFS_Visit(long int v, gnode *node)
{
	err("DFS_VISIT %c\n", (char) v);
	node->color = GRAY;
	foreach(a, node->adj) {
		graph[*a]->time = node->time + 1;
		if (graph[*a]->color == WHITE) {
			err("%c --> ", (char) v);
			DFS_Visit(*a, graph[*a]);
		}
	}
	node->color = BLACK;
	Q.push_back(v);
}

static void topological_sort(void)
{
	foreach(n, graph)
		if ((*n).second->color == WHITE)
			DFS_Visit((*n).first, (*n).second);
	show_order();
	//set_variable_values();
}

int main(void)
{
	int T;

	scanf("%d", &T), gc();
	while (T--) {
		assert(fgets(buffer, 300, stdin) != NULL);
		err("T: %d - buffer: %s", T, buffer);
		read_inequalities();
		topological_sort();
		free_graph();
	}
	return 0;
}
