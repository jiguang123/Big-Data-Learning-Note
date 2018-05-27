#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        num.clear();
        op.clear();
        
        tokenize(input);
        int n = num.size();
        
        vector<int> ans;
        compute(0, n - 1, ans);
        sort(ans.begin(), ans.end());
        
        return ans;
    }
private:
    vector<int> num;
    vector<char> op;
    
    void tokenize(const string &s) {
        int ls = s.length();
        int i = 0;
        int val;
        while (i < ls) {
            val = 0;
            while (i < ls && isdigit(s[i])) {
                val = val * 10 + (s[i] - '0');
                ++i;
            }
            num.push_back(val);
            if (i >= ls) {
                break;
            }
            op.push_back(s[i++]);
        }
    }
    
    int calc(int x, int y, char op) {
        switch(op) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        default:
            return 0;
        }
    }
    
    void compute(int ll, int rr, vector<int> &ans) {
        if (ll == rr) {
            ans.push_back(num[ll]);
            return;
        }
        
        int i, j1, j2;
        vector<int> ans1;
        vector<int> ans2;
        int m1, m2;
        for (i = ll + 1; i <= rr; ++i) {
            compute(ll, i - 1, ans1);
            compute(i, rr, ans2);
            m1 = ans1.size();
            m2 = ans2.size();
            for (j1 = 0; j1 < m1; ++j1) {
                for (j2 = 0; j2 < m2; ++j2) {
                    ans.push_back(calc(ans1[j1], ans2[j2], op[i - 1]));
                }
            }
            ans1.clear();
            ans2.clear();
        }
    }
};