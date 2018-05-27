// 13.3 How does virtual function works in C++?
#include <cstring>
#include <iostream>
using namespace std;

class A {
};

class B {
public:
	void f() {cout << "class B" << endl;};
};

class C {
public:
	C();
};

class D {
public:
	virtual void f() {
		cout << "class D" << endl;
	};
};

class E: public D {
public:
	void f() {
		cout << "class E" << endl;
	};
};

int main()
{
	D *ptr = new E();
	D d;
	E e;
	unsigned ui;
	
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	cout << sizeof(D) << endl;
	cout << sizeof(E) << endl;
	// The result is 1 1 1 4 4 on Visual Studio 2012.
	ptr->f();
	// class with no data member have to occupy 1 byte, so as to have an address.
	// class with virtual functions need a pointer to the virtual function table.
	printf("The address of d is %p.\n", &d);
	printf("The address of e is %p.\n", &e);
	printf("The address of d.f is %p.\n", (&D::f));
	printf("The address of e.f is %p.\n", (&E::f));

	memcpy(&ui, &d, 4);
	printf("d = %X\n", ui);
	memcpy(&ui, &e, 4);
	printf("e = %X\n", ui);
	memcpy(&ui, ptr, 4);
	printf("*ptr = %X\n", ui);

	return 0;
}