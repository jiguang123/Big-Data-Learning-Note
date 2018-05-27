// Solution using balanced BST, time complexity is apparently O(N * log(K))
#include <map>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> &a = nums;
        vector<int> ans;
        int n = a.size();
        if (n == 0 || k == 0) {
            return ans;
        }
        
        int i = 0;
        while (i < k) {
            add(window, a[i++]);
        }
        ans.push_back(window.rbegin()->first);
        while (i < n) {
            remove(window, a[i - k]);
            add(window, a[i++]);
            ans.push_back(window.rbegin()->first);
        }
        
        return ans;
    }
protected:
    map<int, int> window;
    
    void add(map<int, int> &mm, int key) {
        ++mm[key];
    }
    
    void remove(map<int, int> &mm, int key) {
        auto it = mm.find(key);
        if (it == mm.end()) {
            return;
        } else if (it->second == 1) {
            mm.erase(it);
        } else {
            --(it->second);
        }
    }
};