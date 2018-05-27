// 13.2 Expain your understanding on hash table and STL map. If data scale is small, what can be used to replace hash table?
// Answer:
//	Hash table is a data structure which holds item in buckets. Every bucket has a hash number, which is computed by a hashFunction().
//	When inserting or searching in the hash table, the key is passed to the hashFunction() to calculate the corresponding hash number, that will decide which bucket is to hold this item.
//	While there will be multiple elements with the same hash number, known as collision, the hash table has to be equipped with probing strategy, which decides where the next proper position to hold the item is.
//	Three important properties about hash table:
//		1. == operator
//		2. hashFunction()
//		3. probing strategy, such as linear, quadratic, polynomial, chaining and so on
//	A single operation could reach O(1) time, but collision will require extra probing time.
//
//	STL map is a red-black tree, which is a high-balanced binary search tree.
//	The elements in STL map is sorted, as the nodes in a BST is inserted based on comparison.
//	A single operation could reach O(log(n)) time.
//	Two important properties aboutt STL map:
//		1. < operator
//		2. red-black tree
int main()
{
	return 0;
}