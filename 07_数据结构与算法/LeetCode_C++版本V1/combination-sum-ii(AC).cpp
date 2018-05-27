// 1WA, 1AC, #include <algorithm>
// 1WA here, must include algorithm, otherwise sort() would act unexpectedly
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int i, j, n;
        
        n = result.size();
        for(i = 0; i < n; ++i){
            result[i].clear();
        }
        result.clear();
        
        sort(num.begin(), num.end());
        v.clear();
        count.clear();
        i = 0;
        n = num.size();
        // remove duplicates from num
        while(i < n){
            j = i + 1;
            while(j < n && num[i] == num[j]){
                ++j;
            }
            v.push_back(num[i]);
            count.push_back(j - i);
            i = j;
        }
        
        arr.clear();
        n = v.size();
        dfs(0, n, 0, target);
        
        return result;
    }
private:
    vector<int> v;
    vector<int> arr;
    vector<int> count;
    vector<vector<int>> result;
    
    void dfs(int idx, int n, int sum, int target) {
        int i, j, k;
        
        if(sum == target){
            result.push_back(arr);
            return;
        }
        
        if(sum > target){
            return;
        }

        for(i = idx; i < n; ++i){
            for(j = 1; sum + v[i] * j <= target && j <= count[i]; ++j){
                for(k = 0; k < j; ++k){
                    arr.push_back(v[i]);
                }
                dfs(i + 1, n, sum + v[i] * j, target);
                for(k = 0; k < j; ++k){
                    arr.pop_back();
                }
            }
        }
    }
};