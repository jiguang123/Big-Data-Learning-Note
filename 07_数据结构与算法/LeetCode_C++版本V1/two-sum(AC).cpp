// O(n * log(n)) solution with O(n) space
#include <algorithm>
using namespace std;

struct Term {
    int val;
    int i;
};

bool comp(const Term &x, const Term &y)
{
	return x.val < y.val;
}

class Solution {
public:
    /*
     * @param numbers : An array of Integer
     * @param target : target = numbers[index1] + numbers[index2]
     * @return : [index1+1, index2+1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> &a = nums;
        int n = a.size();
        vector<Term> v(n);
        
        int i, j;
        for (i = 0; i < n; ++i) {
            v[i].val = a[i];
            v[i].i = i + 1;
        }
        sort(v.begin(), v.end(), comp);
        
        vector<int> ans(2);
        i = 0;
        j = n - 1;
        while (i < j) {
            if (v[i].val + v[j].val < target) {
                ++i;
            } else if (v[i].val + v[j].val > target) {
                --j;
            } else {
                ans[0] = v[i].i;
                ans[1] = v[j].i;
                if (ans[0] > ans[1]) {
                    swap(ans[0], ans[1]);
                }
                break;
            }
        }
        return ans;
    }
};