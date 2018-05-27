// 6.4 There is an island with a bunch of people living there.
// The strange thing is, any blue-eyed tourists must leave immediately when they find out they're blue-eyed.
// Everyone can see others' eye colors, but not their own.
// They know there'll be at least one blue-eyed tourists. If no more, the game ends.
// Answer:
//	Suppose there're n people and c are blue-eyed.
//	If n == 1, that one will soon find out nobody else is blue-eyed, he'll leave on the 1st day.
//	If n == 2, those two will see one blue-eyed, they are not sure if c == 1 or c == 2.
//	But on the second day, when they still see each other, they know c == 2. Otherwise the one would have left. They'll leave on the 2nd day.
//	With mathematical induction, it can be proven that all the c blue-eyed will leave on the cth day together.
//	The most difficult part for me, is that when they can't be sure, they will simply stay. I thought every day there must've been someone leaving.
int main()
{
	return 0;
}