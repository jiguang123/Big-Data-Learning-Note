// 1WA, 1AC, the simpliest solution is also the best one here.
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        int i, len;
        int last_pos;
        int max_res;
        
        last_pos = -1;
        max_res = 0;
        len = (int)s.length();
        for (i = 0; i < len; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                if (st.empty()) {
                    last_pos = i;
                } else {
                    st.pop();
                    if (st.empty()) {
                        max_res = max(max_res, i - last_pos);
                    } else {
                        max_res = max(max_res, i - st.top());
                    }
                }
            }
        }
        while (!st.empty()) {
            st.pop();
        }
        
        return max_res;
    }
};