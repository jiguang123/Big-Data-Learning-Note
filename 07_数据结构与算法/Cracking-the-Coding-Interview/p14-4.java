// 14.4 tell me about the differences between C++ template and java generics.
// Answer:
//	1. C++ template can be used on built-in type and user-defined types, java generics can only be used on classes. Integer for int, Double for double.
//	2. java generics can put some restrictions on the <T>, such as <T extends superclass>, whereas this is not practical in C++.
//	3. You may use downcast instead of generics, but generics enhance the resuability of code, so is template in C++.
import java.util.Vector;

public class TestJava<T> {
	public T data;

	public TestJava(T data) {
		// TODO Auto-generated constructor stub
		this.data = data;
	}

	String getType() {
		return this.data.getClass().getName();
	}

	public static void main(String[] args) {
		Vector<Integer> v = new Vector<Integer>();
		v.add(2);
		v.add(1);

		TestJava<Vector<Integer>> testJava = new TestJava<Vector<Integer>>(v);
		System.out.println(testJava.getType());
		System.out.println(v);
	}
}