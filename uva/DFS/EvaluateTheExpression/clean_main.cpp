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

char buffer[301];
list<int>  exp; /* expression */
stack<int> st;
bool inconsistent;
Graph graph;
Queue Q;
int casenum = 1;

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

#define gc()	(void) getchar()
static bool read_inequalities(void)
{
	char ca, cb;
	int I;
	scanf("%d", &I), gc();
	while (I--) {
		scanf("%c>%c", &ca, &cb), gc();
		if (!inconsistent)
			add_adjacent(int(cb), int(ca));
	}
	return !inconsistent;
}

static void free_graph(void)
{
	foreach(n, graph)
		delete (*n).second;
	graph.clear();
	Q.clear();
}

static void update_cascade(gnode *node, int time)
{
	node->time = time;
	foreach(a, node->adj) {
		if (graph[*a]->color == GRAY) {
			inconsistent = true;
			break;
		}
		update_cascade(graph[*a], time + 1);
	}
}

static void DFS_Visit(long int v, gnode *node)
{
	node->color = GRAY;
	foreach(a, node->adj) {
		gnode *adj = graph[*a];
		if (node->time >= adj->time && adj->color != GRAY)
			update_cascade(adj, node->time + 1);
		if (adj->color == WHITE && !inconsistent) {
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
	foreach(n, graph) {
		if ((*n).second->color == WHITE)
			DFS_Visit((*n).first, (*n).second);
	}
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

static void process_expression(void)
{
	int v = exp.front();

	while (!exp.empty()) {
		switch (v) {
		case '*':
		case '+': {
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			st.push(v == '*'?  a * b:  a + b);
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
		if (read_inequalities()) { /* if it is consistent */
			topological_sort();
			if (!inconsistent) /* is it still consistent? */
				process_expression();
		}
		free_graph();
	}
	return EXIT_SUCCESS;
}
