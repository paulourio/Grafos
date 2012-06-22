/* UVA 11733 - Airports */
#include <list>
#include <vector>
#include <cstdio>

using namespace std;

struct Edge {
    int from, to, weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {};

    bool operator <(const Edge& b) const 
    {
        return weight < b.weight;
    }
};

static int cities, lines, cost, T;
static list<Edge> edges;
static vector<int> vertices; /* Pai do vértice 3 é vertice[3 - 1] */
static int ncase(1);

static int FindSet(int vertex)
{
    if (vertices[--vertex] != -1)
        while ((vertex = vertices[vertex]))
            if (vertices[vertex] == -1)
                break;
    return vertex;
}

static size_t trees;
static int Kruskal()
{
    int total(0), u, v;
    vertices.clear();
    vertices.resize(cities, -1);
    trees = vertices.size();
    size_t remaining_edges(edges.size());
    while (trees > 1 && remaining_edges-- > 0) {
        Edge e = edges.front();
        edges.pop_front();
        if (e.weight < cost
            && (u = FindSet(e.from)) != (v = FindSet(e.to))) {
            total += e.weight;
            vertices[v] = u; /* Union */
            trees--;
        } else {
            edges.push_back(e);
        }
    }
    return total + cost * trees;
}

static void Go()
{
    int m(lines), from, to, weight;
    edges.clear();
    while (m-- && scanf("%d %d %d", &from, &to, &weight) == 3)
        edges.push_back(Edge(from, to, weight));
    edges.sort();
    int total = Kruskal();
    fprintf(stdout, "Case #%d: %d %ld\n", ncase++, total, trees);
}

int main(void)
{
    vertices.reserve(25);
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &cities, &lines, &cost);
        Go();
    }
    return 0;
}

