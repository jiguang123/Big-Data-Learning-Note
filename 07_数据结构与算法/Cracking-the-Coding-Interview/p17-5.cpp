// 17.5 I am the Master Mind. Guess the number.
// When you guessed the right number at the right position, you got a hit.
// When you guessed the right number at the wrong position, you got a pseudo-hit.
#include <cstdio>
using namespace std;

void check(int solution[], int guess[], int &hit, int &pseudo_hit)
{
	static int c[4];
	static int mark[4];
	
	int i;
	for (i = 0; i < 4; ++i) {
		c[i] = 0;
		mark[i] = 0;
	}
	
	hit = pseudo_hit = 0;
	for (i = 0; i < 4; ++i) {
		if (solution[i] == guess[i]) {
			// hit
			mark[i] = 1;
			++hit;
		} else {
			++c[solution[i]];
		}
	}
	for (i = 0; i < 4; ++i) {
		if (mark[i]) {
			continue;
		}
		// pseudo_hit
		if (c[guess[i]] > 0) {
			mark[i] = 2;
			--c[guess[i]];
			++pseudo_hit;
		}
	}
}

int main()
{
	int solution[4];
	int guess[4];
	int hit, pseudo_hit;
	int i;
	
	while (scanf("%d", &solution[0]) == 1) {
		for (i = 1; i < 4; ++i) {
			scanf("%d", &solution[i]);
		}
		for (i = 0; i < 4; ++i) {
			scanf("%d", &guess[i]);
		}
		check(solution, guess, hit, pseudo_hit);
		printf("%d hit(s), %d pseudo-hit(s).\n", hit, pseudo_hit);
	}
	
	return 0;
}