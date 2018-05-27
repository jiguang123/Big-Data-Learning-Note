// 3.7 Implement a queue that holds cats and dogs. If you want dog or cat, you get the oldest dog or cat. If you want a pet, you get the oldest of them all.
#include <iostream>
#include <string>
using namespace std;

template <class T>
struct ListNode {
	T val;
	long long int id;
	ListNode *next;
	
	ListNode(T _val = 0, long long int _id = 0): val(_val), id(_id), next(nullptr) {};
};

template <class T>
class CatsAndDogs {
public:
	CatsAndDogs() {
		first_cat = last_cat =  first_dog = last_dog = nullptr;
		current_id = 0;
	}
	
	void enqueue(T val, int dog_or_cat) {
		switch (dog_or_cat) {
		case 0:
			// cat
			if (first_cat == nullptr) {
				first_cat = last_cat = new ListNode<T>(val, current_id);
			} else {
				last_cat->next = new ListNode<T>(val, current_id);
				last_cat = last_cat->next;
			}
			break;
		case 1:
			// dog
			if (first_dog == nullptr) {
				first_dog = last_dog = new ListNode<T>(val, current_id);
			} else {
				last_dog->next = new ListNode<T>(val, current_id);
				last_dog = last_dog->next;
			}
			break;
		}
		++current_id;
	}
	
	T dequeueAny() {
		if (first_cat == nullptr) {
			return dequeueDog();
		} else if (first_dog == nullptr) {
			return dequeueCat();
		} else if (first_cat->id < first_dog->id) {
			return dequeueCat();
		} else {
			return dequeueDog();
		}
	}
	
	T dequeueCat() {
		T result;
		
		result = first_cat->val;
		if (first_cat == last_cat) {
			delete first_cat;
			first_cat = last_cat = nullptr;
		} else {
			ListNode<T> *ptr = first_cat;
			first_cat = first_cat->next;
			delete ptr;
		}

		return result;
	}
	
	T dequeueDog() {
		T result;
		
		result = first_dog->val;
		if (first_dog == last_dog) {
			delete first_dog;
			first_dog = last_dog = nullptr;
		} else {
			ListNode<T> *ptr = first_dog;
			first_dog = first_dog->next;
			delete ptr;
		}

		return result;
	}
private:
	ListNode<T> *first_cat;
	ListNode<T> *first_dog;
	ListNode<T> *last_cat;
	ListNode<T> *last_dog;
	long long int current_id;
};

int main()
{
	CatsAndDogs<string> cd;
	string val;
	string type;
	string cmd;
	
	while (cin >> cmd) {
		if (cmd == "end") {
			break;
		} else if (cmd == "in") {
			cin >> type;
			if (type == "cat") {
				cin >> val;
				cd.enqueue(val, 0);
			} else if (type == "dog") {
				cin >> val;
				cd.enqueue(val, 1);
			}
		} else if (cmd == "out") {
			cin >> type;
			if (type == "cat") {
				cout << "cat=" << cd.dequeueCat() << endl;
			} else if (type == "dog") {
				cout << "dog=" << cd.dequeueDog() << endl;
			} else if (type == "any") {
				cout << "any=" << cd.dequeueAny() << endl;
			}
		}
	}
	
	return 0;
}