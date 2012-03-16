#include <cstdio>
#include <list>
#include <map>

using namespace std;

struct gnode {
	int value;
	list<int> adj;
};

typedef map<int, gnode *> Graph;

Graph graph;

int main(void)
{
	int from, to;
	while (scanf("%d %d", &from, &to) == 2) {
		if (graph[from] == NULL)
			graph[from] = new gnode;
		graph[from]->adj.push_back(to);
	}
	/* Freeing the graph.  Sometimes it is not necessary (like maraton) */
	for (Graph::iterator it = graph.begin(); it != graph.end(); it++)
		delete (*it).second;
	return 0;
}
