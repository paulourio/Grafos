#include <cstdio>
#include <vector>

using namespace std;

int main(void)
{
	vector<int> v(10); /* A vector of integers with defined size */
	int i = 0;

	while (scanf("%d", &v.at(i)) == 1)
		i++;

	printf("Read items: %d\n", i);
	return 0;
}
