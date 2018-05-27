// 18.1 add two numbers wihout using arithmetic operator.
#include <iostream>
using namespace std;

int add(int x, int y)
{
	int sum;
	int carry;
	int bx, by;
	int base;
	
	base = 1;
	carry = 0;
	sum = 0;
	while (base != 0) {
		bx = x & base;
		by = y & base;
		base <<= 1;
		sum |= ((bx) ^ (by) ^ carry);
		carry = ((bx & by) || (bx & carry) || (by & carry)) ? base : 0;
	}
	
	return sum;
}

int main()
{
	int x, y;
	
	while (cin >> x >> y) {
		cout << add(x, y) << endl;
	}
	
	return 0;
}