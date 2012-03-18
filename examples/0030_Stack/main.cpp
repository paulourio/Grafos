#include <cstdio>
#include <stack>

using namespace std;

enum { OPEN='(', CLOSE=')' };

/* Walk through buff collecting "(" and ")" and check the consistency */
void check(char *buff)
{
	stack<int> s;

	while (*buff != '\0') {
		switch (*buff) {
		case OPEN:
			s.push(OPEN);
			break;
		case CLOSE:
			if (s.size() > 0) {
				s.pop();
			} else {
				puts("FAIL");
				return;
			}
			break;
		default:
			break;
		}
		buff++;
	}
	if (s.size() > 0)
		puts("FAIL");
	else
		puts("OK");
}

int main(void)
{
	char buff[51];

	while (fgets(buff, 50, stdin) != NULL && *buff != '\n')
		check(buff);
	return 0;
}
