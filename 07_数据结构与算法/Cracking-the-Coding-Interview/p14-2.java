// 14.2 Will the code in finally {} be executed if there is a return statement inside try {} or catch{}?
// The answer is yes.
// OUTPUT:
// Hello world.
// An exception is caught: java.lang.ArrayIndexOutOfBoundsException: 2
// Finally you're here.
public class TestJava {
	public static void main(String[] args) {
		try {
			System.out.println("Hello world.");
			int[] a = new int[2];
			a[2] = 1;
			return;
		} catch (Exception e) {
			// TODO: handle exception
			System.out.println("An exception is caught: " + e);
			return;
		} finally {
			System.out.println("Finally you're here.");
		}
	}
}