// 6.1 There are 20 bottles of pills, all of which have pills of 1g, except one with 1.1g.
// Given a balance that can provides exact measurement, can you devise a method to find out the special bottle with just one try?
// Answer:
//	If you pick n[i] pills from bottle i, the total weight should be sigma(n[i] * 1.0).
//	But there is one with 1.1g pills, that would cause a little deviation to the sum.
//	For example, if we pick i pills from bottle i, the sum should be (20 + 1) * 20 / 2 = 210.
//	The real weight w should be greater than 210, (w - 210) / (1.1 - 1.0) will be the number.
int main()
{
	return 0;
}