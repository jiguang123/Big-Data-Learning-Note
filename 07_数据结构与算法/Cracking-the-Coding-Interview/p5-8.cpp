// 5.8 Given a byte array, set a consecutive bit segment to '1'.
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned char byte;

inline void setBit(vector<byte> &v, int i, int j, int w)
{
	v[i * w / 8 + j / 8] |= (1 << (j - (j >> 3 << 3)));
}

inline int getBit(vector<byte> &v, int i, int j, int w)
{
	return !!(v[i * w / 8 + j / 8] & (1 << (j - (j >> 3 << 3))));
}

int main()
{
	int n, w, h;
	int x1, x2, y;
	vector<byte> v;
	int i, j;
	
	while (scanf("%d%d", &n, &w) == 2) {
		h = n * 8 / w;
		v.resize(n);
		for (i = 0; i < n; ++i) {
			v[i] = 0;
		}
		scanf("%d%d%d", &x1, &x2, &y);
		
		// boundary check is omitted.
		for (i = x1; i <= x2; ++i) {
			setBit(v, y, i, w);
		}
		
		for (i = 0; i < h; ++i) {
			for (j = 0; j < w; ++j) {
				putchar('0' + getBit(v, i, j, w));
			}
			putchar('\n');
		}
	}
	
	return 0;
}