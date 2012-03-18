#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

class Process {
public:
	int id;
	int priority;
	/* Constructor to initialise values */
	Process(int aid, int apriority) :
			id(aid), priority(apriority) {
	}
	/* Override operator "<" for comparison of processes by priority */
	bool operator<(const Process &b) const {
		return priority < b.priority;
	}
};

/* A priority queue, using a vector as container. */
deque<Process> q;

int main(void) {
	int id, pr;

	/* Read process list */
	while (scanf("%d %d", &id, &pr) == 2) {
		Process p(id, pr);
		q.push_back(p);
	}
	/* Print the fair execution order */
	stable_sort(q.begin(), q.end());
	while (!q.empty()) {
		printf("%d\n", q.front().id);
		q.pop_front();
	}
	return 0;
}
