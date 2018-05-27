// 1.2 Implement a function void reverse(char *str) in C or C++ which reverses a null-terminated string.
#include <cstdio>
#include <cstring>
using namespace std;

void reverse(char *str)
{
	if (nullptr == str) {
		return;
	}

	size_t i;
	size_t len = strlen(str);
	char ch;

	for (i = 0; i < len - 1 - i; ++i) {
		ch = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = ch;
	}
}

int main()
{
	char str[1000];

	while (scanf("%s", str) == 1) {
		reverse(str);
		printf("%s\n", str);
	}

	return 0;
}