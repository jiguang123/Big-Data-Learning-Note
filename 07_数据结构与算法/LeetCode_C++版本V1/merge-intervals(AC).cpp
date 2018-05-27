// 1CE, 1RE, 1AC, O(n) solution.
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
/*
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};
*/
bool comparator(const Interval &a, const Interval &b)
{
	if (a.start == b.start) {
		return a.end < b.end;
	} else {
		return a.start < b.start;
	}
}
 
class Solution {
public:
	vector<Interval> merge(vector<Interval> &intervals) {
		int i;
		int n = (int)intervals.size();
		int tmp;
		
		for (i = 0; i < n; ++i) {
			if (intervals[i].start > intervals[i].end) {
				tmp = intervals[i].start;
				intervals[i].start = intervals[i].end;
				intervals[i].end = tmp;
			}
		}
		
		for (i = 1; i < n; ++i) {
			if (!comparator(intervals[i - 1], intervals[i])) {
				// the array is not sorted;
				break;
			}
		}
		if (i < n) {
			sort(intervals.begin(), intervals.end(), comparator);
		}
		
		vector<Interval> result;
		int next_i;
		i = 0;
		while (i < n) {
			next_i = i + 1;
			while (next_i < n) {
				if (intervals[next_i].end <= intervals[i].end) {
					// the next interval is included, thus skipped
					++next_i;
				} else if (intervals[next_i].start <= intervals[i].end) {
					// the next interval is overlapped, thus merged
					intervals[i].end = intervals[next_i].end;
					++next_i;
				} else {
					// the next interval is non-overlapping, jump to next
					break;
				}
			}
			result.push_back(intervals[i]);
			i = next_i;
		}
		
		return result;
	}
};