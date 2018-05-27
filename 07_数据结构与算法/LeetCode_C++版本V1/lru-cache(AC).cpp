// 1WA, 1AC, double-linked list + unordered_map
#include <unordered_map>
using  namespace std;

typedef struct DoubleLinkedListNode{
public:
	int key;
	int value;
	struct DoubleLinkedListNode *left;
	struct DoubleLinkedListNode *right;
	DoubleLinkedListNode(int _key = 0, int _value = 0): key(_key), value(_value), left(nullptr), right(nullptr) {}
}DoubleLinkedListNode;

class LRUCache{
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
		this->size = 0;
		this->head = this->tail = nullptr;
		this->hash_table.clear();
	}
	
	int get(int key) {
		if (size == 0) {
			// the LRU cache is empty.
			return KEY_NOT_FOUND;
		}
		
		unordered_map<int, DoubleLinkedListNode *>::iterator mit;
		
		mit = hash_table.find(key);
		if (mit != hash_table.end()) {
			// the key exists in the cache.
			DoubleLinkedListNode *ptr = mit->second;
			if (ptr == head) {
				// do nothing
			} else if (ptr == tail) {
				// ptr is the tail node.
				tail = ptr->left;
				tail->right = nullptr;
				ptr->left = nullptr;
				ptr->right = head;
				head->left = ptr;
				head = ptr;
			} else {
				// ptr is at middle of the list.
				DoubleLinkedListNode *ptr1, *ptr2;
				ptr1 = ptr->left;
				ptr2 = ptr->right;
				ptr1->right = ptr2;
				ptr2->left = ptr1;
				ptr->left = nullptr;
				ptr->right = head;
				head->left = ptr;
				head = ptr;
			}
			return ptr->value;
		} else {
			// key not found.
			return KEY_NOT_FOUND;
		}
	}
	
	void set(int key, int value) {
		if (capacity == 0) {
			// no room to place anything.
			return;
		}
		
		unordered_map<int, DoubleLinkedListNode *>::iterator mit;
		mit = hash_table.find(key);
		if (mit != hash_table.end()) {
			// the key exists in the cache.
			DoubleLinkedListNode *ptr = mit->second;
			if (ptr == head) {
				// do nothing
			} else if (ptr == tail) {
				// ptr is the tail node.
				tail = ptr->left;
				tail->right = nullptr;
				ptr->left = nullptr;
				ptr->right = head;
				head->left = ptr;
				head = ptr;
			} else {
				// ptr is at middle of the list.
				DoubleLinkedListNode *ptr1, *ptr2;
				ptr1 = ptr->left;
				ptr2 = ptr->right;
				ptr1->right = ptr2;
				ptr2->left = ptr1;
				ptr->left = nullptr;
				ptr->right = head;
				head->left = ptr;
				head = ptr;
			}
			ptr->value = value;
		} else {
			DoubleLinkedListNode *ptr = nullptr;
			if (size < capacity) {
				// still some space left.
				// put the new item at front, not rear.
				ptr = new DoubleLinkedListNode(key, value);
				if (head != nullptr) {
					head->left = ptr;
					ptr->right = head;
				} else {
					tail = ptr;
				}
				head = ptr;
				hash_table[key] = ptr;
				++size;
			} else {
				// capacity is reached.
				ptr = tail;
				hash_table.erase(tail->key);
				ptr->key = key;
				ptr->value = value;
				if (head != tail) {
					tail = ptr->left;
					tail->right = nullptr;
					ptr->left = nullptr;
					ptr->right = head;
					head->left = ptr;
					head = ptr;
				}
				hash_table[key] = ptr;
			}
		}
	}
private:
	static const int KEY_NOT_FOUND = -1;
	int capacity;
	int size;
	DoubleLinkedListNode *head;
	DoubleLinkedListNode *tail;
	unordered_map<int, DoubleLinkedListNode *> hash_table;
};