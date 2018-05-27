// 3WA, 1AC
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        
        int i, len;
        len = digits.size();
        
        if(len <= 0){
            return digits;
        }
        
		// 1WA here, add 1 at the wrong position, you FOOL!!!
        ++digits[len - 1];
		// 1WA here, reversed order..
        for(i = len - 1; i > 0; --i){
            digits[i - 1] += digits[i] / 10;
            digits[i] %= 10;
        }
		// 1WA here, carry propagation here neglected..
        if(digits[0] >= 10){
            int tmp = digits[0] / 10;
            digits[0] %= 10;
            digits.push_back(0);
            for(i = len; i > 0; --i){
                digits[i] = digits[i - 1];
            }
            digits[0] = tmp;
        }
        
        return digits;
    }
};