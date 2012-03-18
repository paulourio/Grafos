#include <cstdio>
#include <list>

using namespace std;

#define foreach(i,l)  for(typeof((l).begin()) i=(l).begin(); i!=(l).end(); i++)

int main(void)
{
	list<int> l;

	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	l.push_back(7);

	foreach(it, l)
		printf("List item: %d\n", *it);
	return 0;
}
