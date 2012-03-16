#include <cstdio>
#include <list>
#include <map>

using namespace std;

struct gnode {
	int value;
	list<int> adj;
};

typedef map<int, gnode> Graph;

Graph graph;

int main(void)
{
	int from, to;
	while (scanf("%d %d", &from, &to) == 2)
		graph[from].adj.push_back(to);
	return 0;
}
