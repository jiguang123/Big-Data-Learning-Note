// 1CE, 5WA, 1AC, really hard
#include <algorithm>
#include <map>
using namespace std;

typedef struct Term {
    int x, y;
    int op;
} Term;

bool comp(const Term &t1, const Term &t2)
{
    // The ordering is most important
    if (t1.x != t2.x) {
        return t1.x < t2.x;
    }
    if (t1.op != t2.op) {
        return t1.op < t2.op;
    }
    if (t1.y != t2.y) {
        if (t1.op == 0) {
            return t1.y > t2.y;
        } else {
            return t1.y < t2.y;
        }
    }
    return false;
}

class Solution {
public:
    vector<pair<int, int> > getSkyline(vector<vector<int> > &buildings) {
        vector<vector<int> > &a = buildings;
        vector<Term> v;
        map<int, int> m;
        int n, i;
        Term t;
        
        n = a.size();
        for (i = 0; i < n; ++i) {
            t.x = a[i][0];
            t.y = a[i][2];
            t.op = 0;
            v.push_back(t);
            t.x = a[i][1];
            t.y = a[i][2];
            t.op = 1;
            v.push_back(t);
        }
        sort(v.begin(), v.end(), comp);
        n = v.size();
        
        vector<pair<int, int> > ans;
        pair<int, int> p;
        int val;
        bool b;
        
        // This is the horizon
        ++m[0];
        i = 0;
        for (i = 0; i < n; ++i) {
            if (v[i].op == 0) {
                // Start of a building
                if (m.rbegin()->first < v[i].y) {
                    p.first = v[i].x;
                    p.second = v[i].y;
                    ans.push_back(p);
                }
                ++m[v[i].y];
            } else {
                // End of a building
                --m[v[i].y];
                b = false;
                if (m[v[i].y] == 0) {
                    b = v[i].y == m.rbegin()->first;
                    m.erase(v[i].y);
                }
                if (b) {
                    p.first = v[i].x;
                    p.second = m.rbegin()->first;
                    ans.push_back(p);
                }
            }
        }
        return ans;
    }
};