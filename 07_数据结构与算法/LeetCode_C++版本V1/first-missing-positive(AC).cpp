// 1AC, unordered_map is a good substitute for map
#include <unordered_map>
using namespace std;

class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        if (A == nullptr || n <= 0) {
            return 1;
        }
        
        unordered_map<int, int> um;
        int result;
        int i;
        
        result = 1;
        for (i = 0; i < n; ++i) {
            if (A[i] > result) {
                um[A[i]] = 1;
            } else if (A[i] < result) {
                continue;
            } else {
                um[result] = 1;
                ++result;
                while (um.find(result) != um.end()) {
                    ++result;
                }
            }
        }
        
        um.clear();
        return result;
    }
};