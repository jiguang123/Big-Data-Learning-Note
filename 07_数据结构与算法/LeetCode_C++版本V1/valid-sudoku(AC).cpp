// 1WA, 1AC, carefully coding is important, think twice before you submit!
#include <cmath>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int n, n2;
        int i, j;
        
        n2 = board.size();
        if(n2 <= 0){
            return true;
        }
        
        tag = new bool*[n2];
        for(i = 0; i < n2; ++i){
            tag[i] = new bool[n2];
        }
        
        bool res = true;
        n = (int)sqrt(1.0 * n2);
        
        // check row
        for(i = 0; i < n2; ++i){
            for(j = 0; j < n2; ++j){
                tag[i][j] = false;
            }
        }
        for(i = 0; res && i < n2; ++i){
            for(j = 0; res && j < n2; ++j){
                if(board[i][j] >= '1' && board[i][j] <= '9'){
                    if(tag[i][board[i][j] - '1']){
                        res = false;
                    }else{
                        tag[i][board[i][j] - '1'] = true;
                    }
                }
            }
        }
        
        // check column
        for(i = 0; i < n2; ++i){
            for(j = 0; j < n2; ++j){
                tag[i][j] = false;
            }
        }
        for(i = 0; res && i < n2; ++i){
            for(j = 0; res && j < n2; ++j){
                if(board[j][i] >= '1' && board[j][i] <= '9'){
                    if(tag[i][board[j][i] - '1']){
                        res = false;
                    }else{
                        tag[i][board[j][i] - '1'] = true;
                    }
                }
            }
        }

        // check block
        for(i = 0; i < n2; ++i){
            for(j = 0; j < n2; ++j){
                tag[i][j] = false;
            }
        }
        for(i = 0; res && i < n2; ++i){
            for(j = 0; res && j < n2; ++j){
                if(board[i / n * n + j / n][i % n * n + j % n] >= '1' && board[i / n * n + j / n][i % n * n + j % n] <= '9'){
                    if(tag[i][board[i / n * n + j / n][i % n * n + j % n] - '1']){
                        res = false;
                    }else{
                        // 1WA here, this else brach is missing!!
                        tag[i][board[i / n * n + j / n][i % n * n + j % n] - '1'] = true;
                    }
                }
            }
        }
        
        for(i = 0; i < n2; ++i){
            delete[] tag[i];
        }
        delete[] tag;
        
        return res;
    }
private:
    bool **tag;
};