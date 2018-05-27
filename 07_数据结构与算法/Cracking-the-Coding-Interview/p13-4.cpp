// 13.4 What's deep copy and shallow copy? Expain their appications in different cases.
// Answer:
//	deep copy:
//		1. pass by value, often used on small data type, built-in data types.
//		2. data is usually persistent, can be seriailzed directly.
//		3. the data to be deep-copied usually represents objects and entities.
//	shallow copy:
//		1. pass by reference or pointer, often used on large struct or class.
//		2. data is volatile, serialization must be done with the help of persistent data type.
//		3. the data to be shallow-copied usually represents relations and mappings between entities.
int main()
{
	return 0;
}