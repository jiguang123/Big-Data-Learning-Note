// 7.1 Suppose you're playing a basketball game, you have two choices:
// A: one shot one hit
// B: three shots two hits
// For what probability of p would you choose A or B.
// 
// Answer:
// P(A) = p;
// P(B) = C(3, 2) * p * p * (1 - p);
// if P(A) < P(B), p < 3 * p * p * (1 - p)
// 1 < 3 * p * (1 - p)
// 3 * p * p - 3 * p + 1 < 0
// There's no root for this equation, thus for any p, 1 > 3 * p * (1 - p)
// Thus for any p, p > 3 * p * (1 - p)
// P(A)> P(B), choosing A will always be better.
int main()
{
	return 0;
}