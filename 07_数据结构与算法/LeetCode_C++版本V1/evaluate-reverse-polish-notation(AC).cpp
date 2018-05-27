// 1AC, simple training on stack operation.
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
	int evalRPN(vector<string> &tokens) {
		int i, n;
		int op1, op2;
		stack<int> nums;
		bool is_op;
		
		n = (int)tokens.size();
		for (i = 0; i < n; ++i) {
			is_op = false;
			if (tokens[i].length() == 1) {
				switch(tokens[i][0]) {
				case '+':
				case '-':
				case '*':
				case '/':
					is_op = true;
					break;
				}
			}
			
			if (is_op) {
				if (nums.size() < 2) {
					// not enough operands
					return 0;
				}
				op2 = nums.top();
				nums.pop();
				op1 = nums.top();
				nums.pop();
				switch (tokens[i][0]) {
				case '+':
					nums.push(op1 + op2);
					break;
				case '-':
					nums.push(op1 - op2);
					break;
				case '*':
					nums.push(op1 * op2);
					break;
				case '/':
					if (op2 == 0) {
						// divide by 0
						return 0;
					}
					nums.push(op1 / op2);
					break;
				}
			} else {
				if (sscanf(tokens[i].c_str(), "%d", &op1) != 1) {
					// invalid integer format
					return 0;
				}
				nums.push(op1);
			}
		}
		int result = nums.top();
		nums.pop();
		
		return result;
	}
};