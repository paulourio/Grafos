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
	int f, t;
	while (scanf("%d %d", &f, &t) == 2) {
		if (graph[f] == NULL)
			graph[f] = new gnode;
		graph[f]->adj.push_back(t);
	}
	return 0;
}
