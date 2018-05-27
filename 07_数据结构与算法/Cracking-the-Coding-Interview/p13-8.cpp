// 13.8 Implement a smart pointer class, which is capable of automatic garbage collection. Count of reference is the key to this problem.
// Answer:
//	int *ref_count;
//	referece count must be int *, instead of int. Think about why.
//	The destructor function is called for (*ref_count) times, only at the last time the real data is freed.
#include <iostream>
using namespace std;

template <class T>
class Pointer {
public:
	Pointer(T *ptr) {
		data = ptr;
		ref_count = new int(1);
	};
	
	Pointer(Pointer<T> &p) {
		data = p.data;
		ref_count = p.ref_count;
		++(*ref_count);
	};
	
	Pointer<T>& operator = (Pointer<T> &p) {
		if (this == &p) {
			// nothing to do.
			return *this;
		}
		if (*ref_count > 0) {
			remove();
		}
		data = p.data;
		ref_count = p.ref_count;
		++(*ref_count);
		
		return *this;
	};
	
	T getData() {
		return *data;
	};

	void setData(const T &val) {
		*data  = val;
	};
	
	~Pointer() {
		remove();
	};
protected:
	T *data;
	int *ref_count;
	
	void remove() {
		--(*ref_count);
		if (*ref_count == 0) {
			// if the reference count becomes 0, the data is never to be found again.
			// it must be freed.
			delete data;
			data = nullptr;
			delete ref_count;
			ref_count = nullptr;
		}
	};
};

int main()
{
	int *ptr = new int(7);
	Pointer<int> p1(ptr);
	Pointer<int> p2(p1);
	
	cout << p1.getData() << endl;
	p2.setData(12);
	cout << p2.getData() << endl;
	
	return 0;
}