// 18.6 Find the smallest one million number among one billion numbers.
// Suppose one billion numbers can fit in memory.
// I'll use a max heap, which runs in O(n * log(k)) time, returns a sorted result.
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class T>
struct myless {
	bool operator () (const T &x, const T &y) {
		return x < y;
	};
};

int main()
{
	int val;
	int n, k;
	int i;
	// max heap
	priority_queue<int, vector<int>, myless<int> > q;
	vector<int> v;
	
	while (cin >> n >> k && (n > 0 && k > 0)) {
		k = k < n ? k : n;
		for (i = 0; i < k; ++i) {
			cin >> val;
			q.push(val);
		}
		
		for (i = k; i < n; ++i) {
			cin >> val;
			if (q.top() > val) {
				q.pop();
				q.push(val);
			}
		}
		while (!q.empty()) {
			v.push_back(q.top());
			q.pop();
		}
		reverse(v.begin(), v.end());
		
		cout << '{';
		for (i = 0; i < k; ++i) {
			i ? (cout << ' '), 1 : 1;
			cout << v[i];
		}
		cout << '}' << endl;
		
		v.clear();
	}
	
	return 0;
}