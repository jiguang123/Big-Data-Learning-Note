// 8CE, 1AC, solution with <map>, I'll try <unordered_map> later.
#include <map>
#include <vector>
using namespace std;

/*
struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};
*/

struct st {
	int x;
	int y;
	st(int _x = 0, int _y = 0): x(_x), y(_y) {};

	bool operator == (const st &other) const {
		return x == other.x && y == other.y;
	}

	bool operator != (const st &other) const {
		return x != other.x || y != other.y;
	}

	bool operator < (const st &other) const {
		if (x == other.x) {
			return y < other.y;
		} else {
			return x < other.x;
		}
	}
};

class Solution {
public:
	int maxPoints(vector<Point> &points) {
		int n = (int)points.size();
		
		if (n <= 2) {
			return n;
		}
		
		map<st, int> um;
		st tmp;
		// special tangent value for duplicate points
		st dup(0, 0);
		
		int i, j;
		map<st, int>::const_iterator umit;
		int dup_count;
		int max_count;
		int result = 0;
		for (i = 0; i < n; ++i) {
			for (j = i + 1; j < n; ++j) {
				tmp.x = points[j].x - points[i].x;
				tmp.y = points[j].y - points[i].y;
				// make sure one tangent value has one representation only.
				normalize(tmp);
				if (um.find(tmp) != um.end()) {
					++um[tmp];
				} else {
					um[tmp] = 1;
				}
			}
			max_count = dup_count = 0;
			for (umit = um.begin(); umit != um.end(); ++umit) {
				if (umit->first != dup) {
					max_count = (umit->second > max_count ? umit->second : max_count);
				} else {
					dup_count = umit->second;
				}
			}
			max_count = max_count + dup_count + 1;
			result = (max_count > result ? max_count : result);
			um.clear();
		}
		
		return result;
	}
private:
	void normalize(st &tmp) {
		if (tmp.x == 0 && tmp.y == 0) {
			// (0, 0)
			return;
		}
		if (tmp.x == 0) {
			// (0, 1)
			tmp.y = 1;
			return;
		}
		if (tmp.y == 0) {
			// (1, 0)
			tmp.x = 1;
			return;
		}
		if (tmp.x < 0) {
			// (-2, 3) and (2, -3) => (2, -3)
			tmp.x = -tmp.x;
			tmp.y = -tmp.y;
		}
		
		int gcd_value;
		
		gcd_value = (tmp.y > 0 ? gcd(tmp.x, tmp.y) : gcd(tmp.x, -tmp.y));
		// (4, -6) and (-30, 45) => (2, -3)
		// using a double precision risks in accuracy
		// so I did it with a pair
		tmp.x /= gcd_value;
		tmp.y /= gcd_value;
	}
	
	int gcd(int x, int y) {
		// used for reduction of fraction
		return y ? gcd(y, x % y) : x;
	}
};