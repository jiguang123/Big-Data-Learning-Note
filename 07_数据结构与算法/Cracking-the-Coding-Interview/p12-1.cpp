// 12.1 What's wrong with the following code segment?
#include <cstdio>
using namespace std;

// unsigned int will never be negative, so it's a dead loop.
// "%d" is not right, should be "%u".
int main()
{
	unsigned int i;
	
	for (i = 100; i >= 0; --i) {
		printf("%d\n", i);
	}
	
	return 0;
}