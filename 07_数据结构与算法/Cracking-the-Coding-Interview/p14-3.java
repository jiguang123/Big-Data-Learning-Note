// 14.3 final, finally and finalize, what are they?
// you can't inherit me
public final class TestJava {
	// you can't modify me
	public final int i = 123;
	public final int j;
	
	public TestJava () {
		j = 2;
		// you can't modify me again.
		// j = 3;
	}
	
	// you can't override me
	public final void f() {
		System.out.println("TestJava.f()");
	};
	
	// a substitute for ~TestJava().
	// it signifies it is ready to be collected, but it doesn't have to be destroyed immediately.
	@ Override
	protected void finalize() {
		System.out.println("finalized");
	};
	
	public static void main(String[] args) {
		TestJava testJava = new TestJava();
		testJava.f();
		testJava.finalize();
	}
}