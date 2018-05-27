// 18.9 A stream of integers are passed to you, you have to tell me the median as they keep coming in.
#include <climits>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <class T>
struct LessFunctor
{
	bool operator() (const T &x, const T &y)
	{
		return x < y;
	}
};

template <class T>
struct GreaterFunctor
{
	bool operator() (const T &x, const T &y)
	{
		return x > y;
	}
};

template <class T>
class MedianArray {
public:
	MedianArray() {
		n_small = 0;
		n_great = 0;
	};
	
	void push(const T& val) {
		if (n_great == 0) {
			greater_heap.push(val);
			++n_great;
			return;
		}
		
		if (n_great > n_small) {
			smaller_heap.push(val);
			++n_small;
		} else {
			greater_heap.push(val);
			++n_great;
		}
		
		if (greater_heap.top() < smaller_heap.top()) {
			T tmp;
			
			tmp = greater_heap.top();
			greater_heap.pop();
			greater_heap.push(smaller_heap.top());
			smaller_heap.pop();
			smaller_heap.push(tmp);
		}
	};
	
	T median() {
		if (n_great == 0) {
			return INT_MIN;
		} else if (n_great > n_small) {
			return greater_heap.top();
		} else {
			return (smaller_heap.top() + greater_heap.top()) / 2;
		}
	};
	
	~MedianArray() {
		n_small = 0;
		n_great = 0;
		while (!greater_heap.empty()) {
			greater_heap.pop();
		}
		while (!smaller_heap.empty()) {
			smaller_heap.pop();
		}
	};
private:
	int n_small;

	// greater elements are stored in here.
	priority_queue<T, vector<T>, GreaterFunctor<T> > greater_heap;

	int n_great;

	// smaller elements are stored in here.
	priority_queue<T, vector<T>, LessFunctor<T> > smaller_heap;
};

int main()
{
	MedianArray<int> ma;
	int val;
	
	while (cin >> val) {
		ma.push(val);
		cout << ma.median() << endl;
	}
	
	return 0;
}