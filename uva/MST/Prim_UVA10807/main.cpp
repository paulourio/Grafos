/* UVA 10807 - Prim */
#include <iostream>
#include <list>
#include <vector>

#ifndef ONLINE_JUDGE
#include <cstdio>
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

using namespace std;

struct Edge {
    int from, to, weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {};

    bool operator <(const Edge& b) const 
    {
        return weight < b.weight;
    }
};

static int cities, lines;
static list<Edge> edges;
static vector<int> vertices; /* Pai do vértice 3 é vertice[3 - 1] */

static int FindSet(int vertex)
{
    if (vertices[--vertex] != -1)
        while ((vertex = vertices[vertex]))
            if (vertices[vertex] == -1)
                break;
    return vertex;
}

static int Kruskal()
{
    int total(0), u, v;
    vertices.clear();
    vertices.resize(cities, -1);
    size_t trees(vertices.size()), remaining_edges(edges.size());
    while (trees > 1 && remaining_edges-- > 0) {
        Edge e = edges.front();
        edges.pop_front();
        if ((u = FindSet(e.from)) != (v = FindSet(e.to))) {
            total += e.weight;
            vertices[v] = u; /* Union */
            trees--;
        } else {
            edges.push_back(e);
        }
    }
    return trees != 1?  -1:  total;
}

static void Go()
{
    int m(lines), from, to, weight;
    edges.clear();
    while (m-- && cin >> from >> to >> weight)
        edges.push_back(Edge(from, to, weight));
    edges.sort();
    int first = Kruskal(), second = Kruskal();
    dbg("first = %d, second = %d\n", first, second);
    if (first < 0 || second < 0)
        cout << "No way!\n";
    else
        cout << first + second << "\n";
}

int main(void)
{
    vertices.reserve(25);
    while (cin >> cities && cities != 0) {
        cin >> lines;
        Go();
    }
    return 0;
}

