#include <cstdio>
#include <queue>

using namespace std;

class Process {
public:
	int id;
	int priority;
	/* Constructor to initialize values */
	Process(int aid, int apriority) :
			id(aid), priority(apriority) {
	}
	/* Override operator "<", for compare processes by priority */
	bool operator<(const Process &rhs) const {
		return priority > rhs.priority;
	}
};

/* A priority queue, using a vector as container. */
priority_queue<Process, vector<Process> > q;

int main(void) {
	int id, pr;

	/* Read process list */
	while (scanf("%d %d", &id, &pr) == 2) {
		Process p(id, pr);
		q.push(p);
	}
	/* Print the fair execution order */
	while (!q.empty()) {
		printf("%d\n", q.top().id);
		q.pop();
	}
	return 0;
}
