// 1RE, 1WA, 1AC  must be more careful
class Solution {
public:
    bool isPalindrome(int x) {
		// 1RE here, ignored the case of INT_MIN
        if(x == INT_MAX || x == INT_MIN){
			return false;
		}
		
		// IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int high, low;
		
		if(x < 0){
			// 1WA here, seems negative number is not palindrome, that's unfair..
			return false;
		}
		
		if(x == 0){
			return true;
		}
		
		high = low = 1;
		while(x / high >= 10){
			high *= 10;
		}
		
		while(high > low){
			if(x / high % 10 != x / low % 10){
				return false;
			}else{
				// fixed, didn't cause a WA, lucky..
				high /= 10;
				low *= 10;
			}
		}
		
		return true;
    }
};