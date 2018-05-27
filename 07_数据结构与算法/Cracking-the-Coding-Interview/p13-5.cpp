// 13.5 Explain the "volatile" keyword in C.
// Answer:
//	1. disable compiler optimization on 'volatile' data.
// 	2. the data declared as volatile won't be cached in register, because it might be modified in memory by other threads or subprocesses.
//	3. 'volatile' is more of an issue to be discussed in DSP design, thus paid less attention than other C keywords.
int main()
{
	return 0;
}