#include <cstdio>
using namespace std;

class BIT {
public:
    BIT(int n) {
        this->n = n;
        v.resize(n + 1, 0);
    }
    
    int lowbit(int x) {
        return x & -x;
    }
    
    int sum(int idx) {
        int i = idx;
        int sum = 0;
        while (i > 0) {
            sum += v[i];
            i -= lowbit(i);
        }
        return sum;
    }
    
    void add(int idx, int val) {
        int i = idx;
        while (i <= n) {
            v[i] += val;
            i += lowbit(i);
        }
    }
    
    int getSum(int idx1, int idx2) {
        return sum(idx2) - sum(idx1 - 1);
    }
protected:
    int n;
    vector<int> v;
};

class Solution {
public:
    vector<int> countSmaller(vector<int> &nums) {
        const int MAXN = 1000000;
        vector<int> v;
        discretize(nums, v);
        
        BIT bit(MAXN);
        int n = v.size();
        int i;
        vector<int> result(n, 0);
        for (i = n - 1; i >= 0; --i) {
            bit.add(v[i], 1);
            result[i] = bit.sum(v[i] - 1);
        }
        
        return result;
    }
protected:
    void discretize(vector<int> &a, vector<int> &v) {
        set<int> ss;
        map<int, int> mm;
        
        int i;
        int n = a.size();
        for (i = 0; i < n; ++i) {
            ss.insert(a[i]);
        }
        
        i = 0;
        for (auto it = ss.begin(); it != ss.end(); ++it) {
            mm[*it] = ++i;
        }
        ss.clear();
        
        v.resize(n);
        for (i = 0; i < n; ++i) {
            v[i] = mm[a[i]];
        }
    }
};
