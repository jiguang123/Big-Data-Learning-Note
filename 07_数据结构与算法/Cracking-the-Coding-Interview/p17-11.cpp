// 17.11 Given a rand5() method, which generates random integer between [0, 4]. Please implement rand7() for [0, 6].
// The key to this problem, is to make sure every number gets the same probability.
#include <cstdio>
#include <cstdlib>
using namespace std;

int rand5()
{
	return rand() % 5;
}

int rand7()
{
	int val;
	
	while (true) {
		val = 5 * rand5() + rand5();
		if (val < 21) {
			return val % 7;
		}
	}
}

int main()
{
	while (true) {
		printf("%d\n", rand7());
	}
	
	return 0;
}