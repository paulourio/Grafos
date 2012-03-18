#include <cstdio>
#include <vector>

using namespace std;

int main(void)
{
	vector<int> v;
	int tmp;

	/* read integers from stdin */
	while (scanf("%d", &tmp) == 1)
		v.push_back(tmp);

	/* iterate over the vector, printing each read value */
	vector<int>::iterator it;
	for (it = v.begin();  it != v.end();  it++)
		printf("%3d", *it);  /* it is a pointer to the int value */
	putchar('\n');

	v.clear(); /* Clear all items */
	return 0;
}
