// 17.12 Given an array of integers and target value, find all pairs in the array that sum up to the target.
// Use hash to achieve O(n) time complexity. Duplicates pairs are skipped.
#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
	vector<int> v;
	unordered_map<int, int> um;
	int n, i;
	int x, y;
	int target;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		scanf("%d", &target);
		
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		
		// duplicate pairs are skipped
		for (i = 0; i < n; ++i) {
			um[v[i]] = um[v[i]] + 1;
		}
		
		unordered_map<int, int>::iterator it, it2;
		for (it = um.begin(); it != um.end(); ++it) {
			x = it->first;
			y = target - x;
			if (x > y) {
				continue;
			}
			
			--it->second;
			if ((it2 = um.find(y)) != um.end() && it2->second > 0) {
				printf("(%d, %d)\n", x, y);
			}
			++it->second;
		}
		
		v.clear();
		um.clear();
	}
	
	return 0;
}