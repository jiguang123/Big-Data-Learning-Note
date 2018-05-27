// 14.1 In terms of inheritance, what is the point of declaring the constructor as private?
// Answer:
//	1. private member cannot be inherited, thus the class cannot be inherited.
//	2. constructor is private, so you cannot new an object freely. Only through public static member method can you get an instance of this class.
//	3. with this you can implement Singleton Pattern, which ensures that a class has at most one instance within an application. You can but you don't have to do it.
public class TestJava {
	private static TestJava instance = null;

	public static TestJava getInstance() {
		if (instance == null) {
			instance = new TestJava();
		}
		return instance;
	}
	
	public void f() {
		System.out.println("TestJava::f()");
	}

	private TestJava() {
	}

	public static void main(String[] args) {
		System.out.println("Hello world.");
		TestJava testJava = TestJava.getInstance();
		testJava.f();
	}
}