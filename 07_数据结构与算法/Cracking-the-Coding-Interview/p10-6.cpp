// 10.6 You have 10 billion URLs, how would you do to detect duplicates in them.
// Answer:
//	1. Use digital sign algorithm to convert string to a number of checksum.
//	2. Use this sign as the hash key, if memory allow, use an in-memory hash table to detect duplicates.
//	3. If memory won't fit in, use K-V database instead. 10GB scale should be acceptable for one machine, so I won't seek help from another computer.
int main()
{
	return 0;
}