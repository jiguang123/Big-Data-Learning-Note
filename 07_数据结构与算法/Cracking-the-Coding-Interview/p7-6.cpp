// 7.6 Find the line that crosses the most points.
#include <unordered_map>
#include <vector>
using namespace std;

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

struct st {
	int x;
	int y;
	st(int _x = 0, int _y = 0): x(_x), y(_y) {};

	bool operator == (const st &other) const {
		return x == other.x && y == other.y;
	};

	bool operator != (const st &other) const {
		return x != other.x || y != other.y;
	};
};

struct line {
	// ax + by + c = 0;
	int a;
	int b;
	int c;
	line(int _a = 0, int _b = 0, int _c = 0): a(_a), b(_b), c(_c) {};
};

struct hash_functor {
	size_t operator () (const st &a) const {
		return (a.x * 1009 + a.y);
	}
};

struct compare_functor {
	bool operator () (const st &a, const st &b) const {
		return (a.x == b.x && a.y == b.y);
	}
};

typedef unordered_map<st, int, hash_functor, compare_functor> st_map;

class Solution {
public:
	int maxPoints(vector<Point> &points, line &result_line) {
		int n = (int)points.size();
		
		if (n <= 2) {
			return n;
		}
		
		st_map um;
		st tmp;
		// special tangent value for duplicate points
		st dup(0, 0);
		
		int i, j;
		st_map::const_iterator umit;
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
					if (umit->second > max_count) {
						max_count = umit->second;
						getLine(umit->first, points[i], result_line);
					}
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
	
	void getLine(st tan, Point p, line &res) {
		res.a = tan.y;
		res.b = -tan.x;
		res.c = -(res.a * p.x + res.b * p.y);
	}
};

int main()
{
	vector<Point> v;
	Solution sol;
	int i, n;
	Point p;
	line res;
	
	while (scanf("%d", &n) == 1) {
		for (i = 0; i < n; ++i) {
			scanf("%d%d", &p.x, &p.y);
			v.push_back(p);
		}
		sol.maxPoints(v, res);
		printf("%d %d %d\n", res.a, res.b, res.c);
		v.clear();
	}
	
	return 0;
}