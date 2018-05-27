// O(1) space
#include <algorithm>
using namespace std;

class Solution {
public:    
    /**
     * @param numbers : Give an array numbers of n integer
     * @return : Find all unique triplets in the array which gives the sum of zero.
     */
    vector<vector<int> > threeSum(vector<int> &nums) {
        vector<int> &a = nums;
        vector<int> v(3);
        int n = a.size();
        
        ans.clear();
        int i, j, k;
        sort(a.begin(), a.end());
        int val;
        i = 0;
        while (i < n) {
            j = i + 1;
            k = n - 1;
            while (j < k) {
                if (a[i] + a[j] + a[k] < 0) {
                    ++j;
                } else if (a[i] + a[j] + a[k] > 0) {
                    --k;
                } else {
                    v[0] = a[i];
                    v[1] = a[j];
                    v[2] = a[k];
                    ans.push_back(v);
                    val = j;
                    j = nextPos(a, k, j);
                }
            }
            i = nextPos(a, n, i);
        }
        return ans;
    }
private:
    vector<vector<int> > ans;
    
    int nextPos(vector<int> &a, int n, int i) {
        int val = a[i];
        while (i < n && a[i] == val) {
            ++i;
        }
        return i;
    }
};