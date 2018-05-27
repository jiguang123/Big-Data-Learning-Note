// 9.1 A child can run up the stair with n staircases. Every time he can hop up by 1, 2 or 3 steps. How many possible way to do this are there?
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	int n;
	int i;
	vector<int> v;
	
	v.push_back(1);
	n = 1;
	while (true) {
		i = v[n - 1];
		if (n >= 2) {
			i += v[n - 2];
		}
		if (n >= 3) {
			i += v[n - 3];
		}
		if (i >= 1000000000) {
			break;
		} else {
			v.push_back(i);
		}
		++n;
	}
	printf("n = %d\n", (int)v.size());
	
	while (scanf("%d", &n) == 1 && n > 0 && n < (int)v.size()) {
		printf("%d\n", v[n]);
	}
	v.clear();
	
	return 0;
}