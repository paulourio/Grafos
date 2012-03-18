#include <cstdio>

using namespace std;

int main(void)
{
	int *b = new int;

	*b = 56;
	printf("b value is %d\n", *b);
	delete b;
	return 0;
}
