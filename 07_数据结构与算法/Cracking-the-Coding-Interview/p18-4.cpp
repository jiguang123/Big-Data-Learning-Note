// 18.4 Count the number of 2s from 0 to n.
#include <iostream>
using namespace std;

int main()
{
	int d, i;
	long long int base;
	long long int sum;
	long long int s[11];
	long long int n;
	
	s[0] = 0;
	base = 1;
	for (i = 1; i < 10; ++i) {
		s[i] = 10 * s[i - 1] + base;
		base *= 10;
	}
	
	while (cin >> n && n > 0) {
		base = 1;
		i = 0;
		while (base * 10 <= n) {
			base *= 10;
			++i;
		}
		
		sum = 0;
		while (n > 0) {
			d = n / base;
			sum += d * s[i];
			if (d > 2) {
				sum += base;
			} else if (d == 2) {
				sum += n % base + 1;
			}
			n %= base;
			
			base /= 10;
			--i;
		}
		
		cout << sum << endl;
	}
	
	return 0;
}