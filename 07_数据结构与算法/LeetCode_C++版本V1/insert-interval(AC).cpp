// 1WA, 1AC, O(n) solution.
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
		int i, n;
		int in1, in2;
		int i1, i2;
		int ll, rr;
		vector<Interval> res;
		
		n = (int)intervals.size();
		if (n == 0) {
			res.push_back(newInterval);
			return res;
		}
		
		ll = newInterval.start;
		rr = newInterval.end;

		if (ll < intervals[0].start) {
			i1 = -1;
			in1 = 0;
		} else if (ll > intervals[n - 1].end) {
			i1 = n - 1;
			in1 = 0;
		} else {
			for (i = 0; i < n - 1; ++i) {
				if (ll >= intervals[i].start && ll <= intervals[i].end) {
					// inside the interval
					i1 = i;
					in1 = 1;
					break;
				} else if (ll > intervals[i].end && ll < intervals[i + 1].start) {
					i1 = i;
					in1 = 0;
					break;
				}
			}
			if (i == n - 1) {
				i1 = i;
				in1 = 1;
			}
		}

		if (rr < intervals[0].start) {
			i2 = -1;
			in2 = 0;
		} else if (rr > intervals[n - 1].end) {
			i2 = n - 1;
			in2 = 0;
		} else {
			for (i = 0; i < n - 1; ++i) {
				if (rr >= intervals[i].start && rr <= intervals[i].end) {
					// inside the interval
					i2 = i;
					in2 = 1;
					break;
				} else if (rr > intervals[i].end && rr < intervals[i + 1].start) {
					i2 = i;
					in2 = 0;
					break;
				}
			}
			if (i == n - 1) {
				i2 = i;
				in2 = 1;
			}
		}
		
		for (i = 0; i < i1; ++i) {
			res.push_back(intervals[i]);
		}
		
		if (i1 == -1) {
			ll = newInterval.start;
		} else if (in1 == 1) {
			ll = intervals[i1].start;
		} else {
			res.push_back(intervals[i1]);
			ll = newInterval.start;
		}
		if (i2 == -1) {
			rr = newInterval.end;
		} else if (in2 == 1) {
			rr = intervals[i2].end;
		} else {
			rr = newInterval.end;
		}
		res.push_back(Interval(ll, rr));
		
		for (i = i2 + 1; i < n; ++i) {
			res.push_back(intervals[i]);
		}
		
		return res;
    }
};