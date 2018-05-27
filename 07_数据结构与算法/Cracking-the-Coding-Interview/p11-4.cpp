// 11.4 Given a file of 20GB containing strings, one word each line. How would you sort them all?
// Answer:
//	1. Split them into 200M pieces.
//	2. For each pieces, use comparison sort or hashing to sort it in memory.
//	3. After sorting each pieces, output it back to a file.
//	4. Merge the 100 pieces with multiprocess, speed up the merging with a heap or something.
//	5. You can't load all full pieces into memory, load one small piece of a piece at a time.
//	6. When this small piece is merged into final result, load the next small piece.
//	7. I suppose it's completely acceptable for a relatively good PC to afford such IO and computation.
int main()
{
	return 0;
}