// FAQ
#include <algorithm>
using namespace std;

class Solution {
public:
    void rotate(int nums[], int n, int k) {
        if (k < 0) {
            k = n - (n - k) % n;
        }
        k %= n;
        reverse(nums, nums + n - k);
        reverse(nums + n - k, nums + n);
        reverse(nums, nums + n);
    }
};