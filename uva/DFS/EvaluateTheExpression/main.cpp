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

list<int>  exp; /* expression */
stack<int> st;

Graph graph;
Queue Q;

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
}

static void move_stack_top_to_exp_list(void)
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
				move_stack_top_to_exp_list();
			}
			st.push(c);
			break;
		case '(':
			st.push(c);
			break;
		case ')':
			while (st.top() != '(')
				move_stack_top_to_exp_list();
			break;
		default:
			exp.push_back(c);
			break;
		}
	}
	while (!st.empty())
		move_stack_top_to_exp_list();
}

int casenum = 1;
static void process_expression(void)
{
	int v = exp.front();

	while (!exp.empty()) {
		switch (v) {
		case '*':
		case '+': {
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			err("Evaluating %d <op> %d\n", a, b);
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
		read_expression();
		err("T: %d - buffer: ", T);
		foreach(e, exp) {
			err("%c", (char) *e);
		}
		err("\n");
		read_inequalities();
		topological_sort();
		process_expression();
		free_graph();
	}
	return 0;
}
