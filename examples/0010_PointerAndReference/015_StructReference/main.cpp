#include <cstdio>

using namespace std;

union flags {
	unsigned int value;
	struct {
		unsigned int low: 8;
		unsigned int high: 8;
	};
};

void byref(flags &myflag)
{
	myflag.value = 0xABCD;
}

void byptr(flags *__f)
{
	__f->value = 0x1487;
}

int main(void)
{
	flags f;

	byref(f);
	printf(" %X + %X \n", f.high, f.low); /* print AB + CD */

	byptr(&f);
	printf(" %X + %X \n", f.high, f.low); /* print 14 + 87 */

	return 0;
}
