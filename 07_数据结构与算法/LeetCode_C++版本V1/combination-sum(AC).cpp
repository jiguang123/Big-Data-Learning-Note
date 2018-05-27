// 1WA, 1OLE, 1AC, dfs trimming condition is a weak point.
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int i, j, n;
        
        n = result.size();
        for(i = 0; i < n; ++i){
            result[i].clear();
        }
        result.clear();
        
        sort(candidates.begin(), candidates.end());
        v.clear();
        i = 0;
        n = candidates.size();
        // remove duplicates from candidates
        while(i < n){
            j = i + 1;
            while(j < n && candidates[i] == candidates[j]){
                ++j;
            }
            v.push_back(candidates[i]);
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
    vector<vector<int>> result;
    
    void dfs(int idx, int n, int sum, int target) {
        int i, j, k;
        
        if(sum == target){
            result.push_back(arr);
            return;
        }
        
        // 1WA here, if(idx >= n || sum > target) is wrong, must check $sum first.
        if(sum > target){
            return;
        }

        for(i = idx; i < n; ++i){
            for(j = 1; sum + v[i] * j <= target; ++j){
                for(k = 0; k < j; ++k){
                    arr.push_back(v[i]);
                }
                dfs(i + 1, n, sum + v[i] * j, target);
                for(k = 0; k < j; ++k){
                    // 1OLE here, $arr, not $v
                    arr.pop_back();
                }
            }
        }
    }
};