#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <map>
#include <list>
#include <queue>
#include <stack>

using namespace std;

#define foreach(i,l)  for(typeof((l).begin()) i=(l).begin(); i!=(l).end(); i++)
#define gc()	(void) getchar()

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

char buffer[301];
list<int>  exp; /* expression */
stack<int> st;
bool inconsistent;
Graph graph;
Queue Q;
int casenum = 1;

static gnode *get_node(int v) /* Used only while creating the graph */
{
	gnode *node = graph[v];
	if (node == NULL) {
		node = new gnode;
		node->color = WHITE;
		node->time = 1;
		graph[v] = node;
	}
	return node;
}

static void add_adjacent(int a, int b)
{
	if (a == b) {
		printf("Case %d: -1\n", casenum++);
		inconsistent = true;
		return;
	}
	gnode *gb = get_node(b);
	get_node(a)->adj.push_back(b);
	foreach(adjb, gb->adj)
		if (*adjb == a) {
			printf("Case %d: -1\n", casenum++);
			inconsistent = true;
			break;
		}
}

static bool read_inequalities(void)
{
	char ca, cb;
	int I;
	scanf("%d", &I), gc();
	err("\tI: %d\n", I);
	while (I--) {
		scanf("%c>%c", &ca, &cb), gc();
		if (!inconsistent) {
			err("\tAdding %c > %c\n", ca, cb);
			add_adjacent(int(cb), int(ca));
		}
	}
	return !inconsistent;
}

static void free_graph(void)
{
	foreach(n, graph)
		delete n->second;
	graph.clear();
	Q.clear();
}

static void show_order(void)
{
	err("Topological result:\n");
	if (Q.empty())
		err("\tEmpty. All values are 1\n");
	while (!Q.empty()) {
		err("\t%c (Value: %d)\n", Q.front(), graph[Q.front()]->time);
		Q.pop_front();
	}
}

static void update_cascade(int node_value, gnode *node, int time)
{
	err("\tupdate %c to %d\n", (char) node_value, time);
	node->time = time;
	foreach(a, node->adj) {
		gnode *adj = graph[*a];

		if (adj->color == GRAY) {
			inconsistent = true;
			break;
		}
		update_cascade(*a, adj, time + 1);
	}
}

static void DFS_Visit(long int v, gnode *node)
{
	err("DFS_VISIT %c (value: %d)\n", (char) v, node->time);
	node->color = GRAY;
	foreach(a, node->adj) {
		gnode *adj = graph[*a];

		if (node->time >= adj->time && adj->color != GRAY)
			update_cascade(*a, adj, node->time + 1);

		if (adj->color == WHITE && !inconsistent) {
			err("%c --> ", (char) v);
			DFS_Visit(*a, adj);
		} else if (adj->color == GRAY || inconsistent) {
			printf("Case %d: -1\n", casenum++);
			inconsistent = true;
			return;
		}
	}
	node->color = BLACK;
	Q.push_back(v);
}

static void topological_sort(void)
{
	foreach(n, graph)
		if (n->second->color == WHITE)
			DFS_Visit(n->first, n->second);
	show_order();
}

static inline void pop_stack_into_expression_list(void)
{
	int pop = st.top();
	st.pop();
	if (pop != '(')
		exp.push_back(pop);
}

#define is_parenthesis(c)	(c == '(' || c == ')')
#define precedence(a,b)		(a - b)
static void read_expression(void)
{
	exp.clear();
	while (!st.empty())
		st.pop();
	int c;
	while ((c = getchar()) != '\n') {
		switch (c) {
		case '*':
		case '+':
			while (!st.empty()) {
				if (is_parenthesis(st.top()))
					break;
				if (precedence(c, st.top()) <= 0)
					break;
				pop_stack_into_expression_list();
			}
			/* no break */
		case '(':
			st.push(c);
			break;
		case ')':
			while (st.top() != '(')
				pop_stack_into_expression_list();
			break;
		default:
			exp.push_back(c);
			break;
		}
	}
	while (!st.empty())
		pop_stack_into_expression_list();
}

static void process_expression(void)
{
	int v = exp.front();

	while (!exp.empty()) {
		switch (v) {
		case '*':
		case '+': {
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			err("Evaluating %d %c %d\n", a, v, b);
			if (v == '*')
				st.push(a * b);
			else
				st.push(a + b);
			break;
		}
		default:
			if (graph[v] != NULL)
				st.push(graph[v]->time);
			else
				st.push(1);
			break;
		}
		exp.pop_front();
		v = exp.front();
	}
	printf("Case %d: %d\n", casenum++, st.top());
}

int main(void)
{
	int T;

	scanf("%d", &T), gc();
	while (T--) {
		inconsistent = false;
		read_expression();
		err("T: %d - buffer: %s", T, buffer);
		foreach(e, exp)
			err("%c", (char) *e);
		err("\n");
		if (read_inequalities()) { /* if it is consistent */
			topological_sort();
			if (!inconsistent)
				process_expression();
		}
		free_graph();
	}
	return EXIT_SUCCESS;
}
