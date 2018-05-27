// 13.6 If a class is defined as base class, why must its destructor be declared "virtual"?
// Answer:
//	If the destructor of base class is declared "virtual", it will be called when a derived class object is being destroyed.
//	Otherwise it wouldn't. As base class may already have some allocated data or other resources, the destructor of basic class must be called to clear them up.
//	Missing the base class destructor will leave out those data allocated for base class, causing memory leakage.
//	Even though there're no dynamically allocated data, the base class should be declared "virtual", as a good practice of coding.
class A {
public:
	virtual ~A() {};
};

class B: public A {
public:
	~B() {};
};

int main()
{
	A *ptr = new B();
	delete ptr;
	// Here ~B() will be called first, ~A() to follow.
	return 0;
}