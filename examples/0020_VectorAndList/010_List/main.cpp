#include <cstdio>
#include <list>

using namespace std;

int main(void)
{
	int ints[] = {16, 2, 77, 29};
	/* Initializating l with iteration from ints to ints+4 */
	list<int> l(ints, ints + 4);

	l.sort();
	list<int>::iterator it;
	for (it = l.begin();  it != l.end();  it++)
		printf("%3d", *it);
	putchar('\n');
	return 0;
}
