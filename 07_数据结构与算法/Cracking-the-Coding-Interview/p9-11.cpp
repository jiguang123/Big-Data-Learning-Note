// 9.11 For a boolean expression and a target value, calculate how many ways to use parentheses on the expression to achieve that value.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void booleanExpressionParentheses(string exp, int target, int &result, vector<string> &one_path, vector<vector<string> > &path)
{
	if ((int)exp.length() == 1) {
		if (exp[0] - '0' == target) {
			path.push_back(one_path);
			++result;
		}
		return;
	}
	
	string new_exp;
	int i, j;
	for (i = 1; i < (int)exp.length(); i += 2) {
		new_exp = "";
		
		for (j = 0; j < i - 1; ++j) {
			new_exp.push_back(exp[j]);
		}
		
		if (exp[i] == '&') {
			new_exp.push_back(((exp[i - 1] - '0') & (exp[i + 1] - '0')) + '0');
		} else if (exp[i] == '|') {
			new_exp.push_back(((exp[i - 1] - '0') | (exp[i + 1] - '0')) + '0');
		} else if (exp[i] == '^') {
			new_exp.push_back(((exp[i - 1] - '0') ^ (exp[i + 1] - '0')) + '0');
		}
		
		for (j = i + 2; j < (int)exp.length(); ++j) {
			new_exp.push_back(exp[j]);
		}
		one_path.push_back(new_exp);
		booleanExpressionParentheses(new_exp, target, result, one_path, path);
		one_path.pop_back();
	}
}

int main()
{
	int result;
	int target;
	int i, j;
	string exp;
	vector<vector<string> > path;
	vector<string> one_path;
	
	while (cin >> exp >> target) {
		result = 0;
		one_path.push_back(exp);
		booleanExpressionParentheses(exp, target, result, one_path, path);
		one_path.pop_back();
		for (i = 0; i < (int)path.size(); ++i) {
			cout << "Path " << i + 1 << endl;
			for (j = 0; j < (int)path[i].size(); ++j) {
				cout << path[i][j] << endl;
			}
			cout << endl;
		}

		for (i = 0; i < (int)path.size(); ++i) {
			path[i].clear();
		}
		path.clear();
		one_path.clear();

		cout << "Total number of ways to achieve the target value is " << result << "." << endl;
	}
	
	return 0;
}