#include <cstdio>

using namespace std;

/* It should copy "from"'s value to "to" and set "from" to zero. */
void moveint(int &to, int from)
{
	to = from;
	from = 0;
}

int main(void)
{
	int a = 32;
	int b = 11;

	moveint(a, b);
	printf("a = %d \t b = %d \n", a, b);
	/* a got "11" but b isn't 0, because we didn't pass its reference */
	return 0;
}
