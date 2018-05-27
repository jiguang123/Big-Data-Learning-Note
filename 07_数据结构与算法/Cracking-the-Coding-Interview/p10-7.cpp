// 10.7 You have a search engine, the main backend has a cluster of 100 machines. If the processSearch(string query) method is the main procedure to handle the search. How would you design the caching strategy?
// Answer:
// Load balancing:
// 	1. Keep strict watch on CPU, IO and memory usage. If occupation is too heavy, start forwarding the incoming requests to its next neighbors.
//	2. Cache may be multi-level, secondary level cache may be used to enlarge cache results, saving the energy of doing new searches.
//	3. If the hit rate of cache is getting abnormally low, force the cache to clear up. These things do happen when some kind of popular events occur. People will flood in to search about some event, and the old results in cache is no longer useful.
//		For example, if the debris of aircraft MH370 is found, there will be awfully lot of searches about it within one miniute. The cache has to be refreshed.
// Caching:
//	1. Every string is computed as digital sum, which is an unsigned integer.
//	2. The integer is modulo by num_of_machine in the cluster to get a remainder, this query is usually processed by machine[remainder].
//	3. The cache on machine[remainder] most likely will have ready result for the query.
//	4. If the machine is too busy, however, it will forward the request to its next alive neighbor.
// After all, none of the strategies come out of nowhere, it must be drawn from observation, and verified with real experiments.
int main()
{
	return 0;
}