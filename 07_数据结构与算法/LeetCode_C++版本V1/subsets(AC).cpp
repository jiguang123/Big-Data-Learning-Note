// 2CE, 1OLE, 1RE, 4WA, 1AC, so difficult...
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, n;
        
        n = result.size();
        for(i = 0; i < n; ++i){
            result[i].clear();
        }
        result.clear();
        // 1WA here, S is not sorted, thus need sorting to ensure that the result is sorted
        sort(S.begin(), S.end());
        arr.clear();
        n = S.size();
		// 1CE here, ; is missing after dfs
        dfs(0, n, S);
        
        return result;
    }
private:
    vector<vector<int>> result;
    vector<int> arr;
    
	// 1CE here, S is not declared in this scope
    void dfs(int idx, int n, vector<int> &S) {
		// 1RE here, didn't check n, out of range
		// 1WA here, only push result when idx == n, or else would have redundant results.
        if(idx == n){
            result.push_back(arr);
            return;
        }
        
		// 1OLE here, for(i = idx; i < n; ++i) structure is wrong, need no for
        dfs(idx + 1, n, S);
        arr.push_back(S[idx]);
        dfs(idx + 1, n, S);
        arr.pop_back();
    }
};