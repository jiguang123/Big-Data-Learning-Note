// 2CE, 1AC
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<string> tokens;
        string token;
        
        int i, j, n;
        
        tokens.clear();
        n = path.length();
        if(n <= 0){
            return "/";
        }
        
        i = 0;
        while(i < n){
            while(i < n && path[i] == '/'){
                ++i;
            }
            j = i + 1;
            while(j < n && path[j] != '/'){
                ++j;
            }
            
            if(i >= n){
                break;
            }
            token = path.substr(i, j - i);
            if(token == ".."){
                if(tokens.size() > 0){
                    tokens.pop_back();
                }
            }else if(token != "."){
                // 2CE here, parameter missing, tokens.push_back();
                tokens.push_back(token);
            }
            
            i = j;
        }
        
        string res;
        
        if(tokens.size() <= 0){
            return "/";
        }else{
            res = "";
            for(i = 0; i < tokens.size(); ++i){
                res = res + "/" + tokens[i];
            }
            tokens.clear();
            return res;
        }
    }
};