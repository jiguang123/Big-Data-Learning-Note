// 10.5 Assume that you're writing a web crawler, how would you avoid going into an infinite loop?
// Answer:
//	Every crawler starts from a seed link, and performs multithread BFS to go down the website and fetch webpages.
//	Every link visited will be put into a hash table. In case there is a loop, the link will be found in the hash table and will not be visited again.
int main()
{
	return 0;
}