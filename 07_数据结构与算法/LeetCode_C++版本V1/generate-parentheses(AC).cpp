// 1AC, simple recursion will do, but keep your mind clear or it's easy to get things complicated
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        result.clear();
        
        dfs(n, n, "");
        
        return result;
    }
private:
    vector<string> result;
    
    void dfs(int cl, int cr, string pat) {
        if(cl == 0 && cr == 0){
            result.push_back(pat);
        }
        
        int i;
        if(cl < cr){
            if(cl > 0){
                dfs(cl - 1, cr, pat + "(");
            }
            if(cr > 0){
                dfs(cl, cr - 1, pat + ")");
            }
        }else if(cl == cr){
            if(cl > 0){
                dfs(cl - 1, cr, pat + "(");
            }
        }else{
            return;
        }
    }
};