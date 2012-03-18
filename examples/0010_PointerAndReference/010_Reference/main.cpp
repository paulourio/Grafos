#include <cstdio>

using namespace std;

int main(void)
{
	int a = 0;

	int *ptr = &a;  /* ptr receives the address of a */
	int &ref = a;	/* ref receives the reference of a */
	/* Both ptr and ref will affect a values.  The difference is how
	 * we use them.
	 */

	*ptr = 1; /* Set value of a */
	printf("a = %d \n", a);

	ref = 2; /* Set value of a */
	printf("a = %d \n", a);

	return 0;
}
