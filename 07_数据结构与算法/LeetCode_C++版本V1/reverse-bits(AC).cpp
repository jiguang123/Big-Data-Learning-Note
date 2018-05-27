// 1AC, I'm beginning to doubt the quality of leetcode problem set...
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int i;
        uint32_t ans = 0;
        for (i = 0; i < sizeof(uint32_t) * 8; ++i) {
            ans = (ans << 1) | (n & 1);
            n >>= 1;
        }
        
        return ans;
    }
};