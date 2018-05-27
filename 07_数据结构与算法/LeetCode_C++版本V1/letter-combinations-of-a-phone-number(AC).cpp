// 7CE, 2RE, 1WA, 1AC, too bad~
#include <string>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        result.clear();
        
        dfs(digits, 0, "");
        
        return result;
    }
private:
    vector<string> result;
    string dict[10] = {
        " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };
    
    void dfs(string &digits, int idx, string str) {
        if(idx == digits.length()){
            result.push_back(str);
            // 1RE here, didn't return
            return;
        }
        
        // 7CE here, dict[digits[idx] - '0'], type mismatch
        for(int i = 0; i < dict[digits[idx] - '0'].length(); ++i){
            // 1RE here, 1WA here, wrong index
            dfs(digits, idx + 1, str + dict[digits[idx] - '0'][i]);
        }
    }
};