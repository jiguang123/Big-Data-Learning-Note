// 18.2 shuffle a deck of 52 cards, it must be perfect random.
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

void printCards(const vector<int> &cards)
{
	int i;
	int n = (int)cards.size();
	const int col = 8;
	
	for (i = 0; i < n; ++i) {
		printf((i % col == col - 1 ? "%4d\n" : "%4d "), cards[i]);
	}
	printf("\n");
}

void shuffleCards(vector<int> &cards)
{
	vector<int> v;
	
	v = cards;
	int i, j;
	int n, n0;
	int idx;
	
	n0 = n = (int)cards.size();
	for (i = 0; i < n0; ++i) {
		idx = rand() % n;
		cards[i] = v[idx];
		--n;
		for (j = idx; j < n; ++j) {
			v[j] = v[j + 1];
		}
	}
	
	v.clear();
}

int main()
{
	srand((unsigned)time(NULL));
	vector<int> cards;
	int i;
	const int n = 52;
	
	cards.resize(n);
	for (i = 0; i < n; ++i) {
		cards[i] = i;
	}
	
	shuffleCards(cards);
	printCards(cards);
	
	return 0;
}