// 10.3 Assume you have a list of 4 billion non-negative integers, you're given 1GB memory. Try to find out a number that is not contained in the number list.
// Answer:
//	1GB means 8Gbit, thus we can use 4 billion bit vector, of actual size 500MB. Scan the list for one pass and mark the existent as '1'.
//	Scan the bit vector to find the first '0' number.
// Extension: if you have only 10MB memory, what's it gonna be then?
// Answer:
//	10MB means 80Mbit, thus we have to scan the list for multiple time. Every time the bit vector covers only part of the range.
//	Such as 0~999, 1000~199, ..., 3999999000~3999999999
//	For each interval, we scan the all numbers and check if there is missing element in the bit vector. If found, return it. Otherwise go on until the last interval.
//	the length of the interval should be carefully chosen, to minimize total number of scannings.
int main()
{
	return 0;
}