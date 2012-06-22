#include <algorithm>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <iostream>

#ifndef ONLINE_JUDGE
#include <cstdio>
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

using namespace std;

static string input, previous;
static list<int> sorted;

struct Node {
    enum Color { BLACK, GRAY, WHITE };
    Color color;
    int value;
    list<Node*> adj;
    Node(int v) : color(WHITE), value(v) {};
};

typedef vector<Node> Graph;

static Graph graph;

static void DFS_Visit(Node& n)
{
    n.color = Node::GRAY;
    list<Node*>::iterator i;
    for (i = n.adj.begin(); i != n.adj.end(); i++) {
        Node &adj(**i);
        if (adj.color == Node::WHITE)
            DFS_Visit(adj);
    }
    n.color = Node::BLACK;
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
    graph.reserve(26);
}

static void ShowGraph()
{
    list<int>::iterator i;
    for (i = sorted.begin(); i != sorted.end(); i++) 
        cout << static_cast<char>(*i);
    cout << endl;
}

static Node* CreateNode(Node node)
{
    Graph::iterator i;

    for (i = graph.begin(); i != graph.end(); i++)
        if (i->value == node.value)
            return &(*i);
    graph.push_back(node);
    return &graph.back();
}

static void Solve()
{
    DFS();
    ShowGraph();
}

#define min(a,b) (a > b? b: a)
static void AnalyseInput()
{
    size_t i(0), size = min(previous.size(), input.size());

    dbg("Compare(%s, %s)\n", previous.c_str(), input.c_str());
    while (i < size) {
        int p = static_cast<int>(previous[i]);
        int n = static_cast<int>(input[i]);
        if (p != n) {
            dbg("Add %c < %c\n", char(p), char(n));
            Node* prev(CreateNode(Node(p)));
            prev->adj.push_back(CreateNode(Node(n)));
            break;
        }
        i++;
    }
}

int main(void)
{
    CreateGraph();
    while (true) {
        cin >> input;
        if (input.compare("#") == 0) {
            Solve();
            return 0;
        }
        if (!previous.empty()) 
            AnalyseInput();
        previous = string(input);
    }
	return 0;
}
