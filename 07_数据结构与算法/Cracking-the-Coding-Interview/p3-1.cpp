// 3.1 Use an array to implement three stacks.
// three fixed-length stacks
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

template <class T>
class ThreeStack {
public:
	ThreeStack(size_t _total_capacity = 1): total_capacity(_total_capacity) {
		msize[0] = 0;
		msize[1] = 0;
		msize[2] = 0;
		
		mcapacity[0] = mcapacity[1] = mcapacity[2] = total_capacity / 3;
		mcapacity[0] += (total_capacity % 3 != 0 ? 1 : 0);
		mcapacity[1] += (total_capacity % 3 == 2 ? 1 : 0);
		
		offset[0] = 0;
		offset[1] = offset[0] + mcapacity[0];
		offset[2] = offset[1] + mcapacity[1];
		
		mdata.resize(total_capacity);
	}
	
	~ThreeStack() {
		mdata.clear();
	}
	
	void push(int idx, T val) {
		if (msize[idx] == mcapacity[idx]) {
			// this stack is full
			return;
		}
		
		mdata[offset[idx] + msize[idx]] = val;
		++msize[idx];
	}
	
	void pop(int idx) {
		if (msize[idx] == 0) {
			return;
		}
		
		--msize[idx];
	}
	
	T top(int idx) {
		if (msize[idx] == 0) {
			return mdata[-1];
		}
		
		return mdata[offset[idx] + msize[idx] - 1];
	}
	
	size_t size(int idx) {
		return msize[idx];
	}
private:
	// total capacity of all stack
	size_t total_capacity;
	// starting offset for each stack
	size_t offset[3];
	// capacities of the three stacks
	size_t mcapacity[3];
	// sizes of the three stacks
	size_t msize[3];
	// the data in the stacks
	vector<T> mdata;
};

int main()
{
	int n;
	size_t idx;
	int val;
	char str[100];
	
	scanf("%d", &n);
	ThreeStack<int> ts(n);
	while (scanf("%s", str) == 1) {
		if (strcmp(str, "end") == 0) {
			break;
		} else if (strcmp(str, "push") == 0) {
			scanf("%u%d", &idx, &val);
			ts.push(idx, val);
		} else if (strcmp(str, "pop") == 0) {
			scanf("%u", &idx);
			ts.pop(idx);
		} else if (strcmp(str, "top") == 0) {
			scanf("%u", &idx);
			printf("top[%u] = %d\n", idx, ts.top(idx));
		} else if (strcmp(str, "size") == 0) {
			scanf("%u", &idx);
			printf("size[%u] = %u\n", idx, ts.size(idx));
		}
	}
	
	return 0;
}