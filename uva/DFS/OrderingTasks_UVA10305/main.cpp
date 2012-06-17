#include <algorithm>
#include <map>
#include <list>
#include <vector>
#include <iostream>

#ifndef ONLINE_JUDGE
#include <cstdio>
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

using namespace std;

int n, m, i, j;

list<int> sorted;

struct Node {
    enum Color { BLACK, GRAY, WHITE };
    Color color;
    int value;
    list<Node*> adj;
    Node(Color c, int v) : color(c), value(v) {};
};

typedef vector<Node> Graph;

Graph graph;

static void DFS_Visit(Node& n)
{
    dbg("DFS_Visit(%d)\n", n.value);
    n.color = Node::GRAY;
    list<Node*>::iterator i;
    for (i = n.adj.begin(); i != n.adj.end(); i++) {
        Node &n(**i);
        if (n.color == Node::WHITE)
            DFS_Visit(n);
    }
    n.color = Node::BLACK;
    dbg("push_front(%d)\n", n.value);
    sorted.push_front(n.value);
}

static void DFS()
{
    Graph::iterator i;
    for (i = graph.begin(); i != graph.end(); i++) 
        if (i->color == Node::WHITE)
            DFS_Visit(*i);
}

static void CreateGraph()
{
    graph.clear();
    sorted.clear();
    graph.reserve(n);
}

static void ShowGraph()
{
    list<int>::iterator i;
    for (i = sorted.begin(); i != sorted.end(); i++) {
        if (i != sorted.begin())
            cout << " ";
        cout << *i;
    }
    for (int x = 1; x <= n; x++) 
        if (find(sorted.begin(), sorted.end(), x) == sorted.end())
            cout << " " << x;
    cout << endl;
}

static Node* CreateNode(Node node)
{
    Graph::iterator i;

    for (i = graph.begin(); i != graph.end(); i++) {
        if (i->value == node.value)
            return &(*i);
    }
    graph.push_back(node);
    return &graph.back();
}

static void Solve()
{
    CreateGraph();
    dbg("Grafo criado n=%d, m=%d\n", n, m);
        while (m--) {
        cin >> i >> j; // i antes de j
        Node& nn = *CreateNode(Node(Node::WHITE, i));
        nn.adj.push_back(CreateNode(Node(Node::WHITE, j)));
    }
    dbg("Lido\n");
    DFS();
    dbg("Mostrando\n");
    ShowGraph();
}

int main(void)
{
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        Solve();
    }
	return 0;
}
