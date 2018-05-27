// 1WA, 1AC
class Solution {
public:
	bool isValid(string s) {
		// IMPORTANT: Please reset any member data you declared, as
		// the same Solution instance will be reused for each test case.
		if(s == ""){
			return true;
		}
		
		stack = new char[s.length()];
		if(stack == nullptr){
			return false;
		}
		
		bool ret;
        int i, len;
        
        pc = 0;
        len = s.length();
		ret = true;
        for(i = 0; i < len; ++i){
			switch(s[i]){
				case '(':
				case '[':
				case '{':
					stack[pc++] = s[i];
					break;
				case ')':
					if(pc <= 0 || stack[pc - 1] != '('){
						ret = false;
					}else{
						--pc;
					}
					break;
				case ']':
					if(pc <= 0 || stack[pc - 1] != '['){
						ret = false;
					}else{
						--pc;
					}
					break;
				case '}':
					if(pc <= 0 || stack[pc - 1] != '{'){
						ret = false;
					}else{
						--pc;
					}
					break;
				default:
					ret = false;
					break;
			}
			if(!ret){
				break;
			}
		}
		// 1WA here, if stack is not empty, the sequence is invalid.
        if(pc != 0){
			ret = false;
		}
		
        delete[] stack;
        stack = nullptr;
		return ret;
    }
private:
    char *stack;
    int pc;
};