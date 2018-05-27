// 12.2 A program crashes when it is run. After running it on a same machine for 10 times, it crashes every time on a different spot.
// It is single-threaded, and uses only C-standard libraries.
// Answer:
//	One different thing when the program is run every time, is the timestamp.
//	So you might check the code where functions about time is called, or timestamp is used.
//	To debug a bugged system, use logging strategy to aid you.
//	Two tips for debugging:
//		1. start printing log at both ends, every time you crashes, shrink the range of debugging by half. Use the ideas of binary search for debug.
//		2. print every suspicious variable if necessary.
int main()
{
	return 0;
}