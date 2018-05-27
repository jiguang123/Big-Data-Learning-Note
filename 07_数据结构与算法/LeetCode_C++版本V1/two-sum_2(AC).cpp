// The O(n) solution by hashing
#include <unordered_map>
using namespace std;

class Solution {
public:
    /*
     * @param numbers : An array of Integer
     * @param target : target = numbers[index1] + numbers[index2]
     * @return : [index1+1, index2+1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> &a = nums;
        vector<int> ans;
        int n = a.size();
        unordered_map<int, int> um;
        unordered_map<int, int>::iterator it;
        
        int i;
        for (i = 0; i < n; ++i) {
            it = um.find(target - a[i]);
            if (it != um.end()) {
                ans.push_back(it->second + 1);
                ans.push_back(i + 1);
                break;
            }
            um[a[i]] = i;
        }
        return ans;
    }
};