// 14.6 Implement a circular array, which allows easy rotation and array access.
// Combination of a vector and a rotation index.
import java.io.PrintStream;
import java.util.Vector;

public class CircularArray<T> {
	public int rotateIndex;
	public Vector<T> v;

	public CircularArray() {
		v = new Vector<T>();
		rotateIndex = 0;
	}

	public T elementAt(int index) {
		if (index < 0 || index > v.size() - 1) {
			throw new ArrayIndexOutOfBoundsException();
		}
		return v.elementAt((index + rotateIndex) % v.size());
	}

	public void add(T val) {
		if (v.size() > 0) {
			v.insertElementAt(val, (rotateIndex + v.size() - 1) % v.size() + 1);
			if (rotateIndex > 0) {
				++rotateIndex;
			}
		} else {
			v.insertElementAt(val, 0);
		}
	}

	public void removeElementAt(int index) {
		if (rotateIndex > 0) {
			if (index < 0 || index > v.size() - 1) {
				throw new ArrayIndexOutOfBoundsException();
			}
			int tmp = v.size();
			v.removeElementAt((index + rotateIndex) % v.size());
			if (index >= tmp - rotateIndex && index <= tmp - 1) {
				--rotateIndex;
			}
		} else {
			v.removeElementAt(index);
		}
	}

	public void rotate(int index) {
		if (v.size() == 0) {
			return;
		}
		index = (v.size() - (v.size() - index) % v.size()) % v.size();
		rotateIndex = (rotateIndex + index) % v.size();
	}

	public static void main(String[] args) {
		CircularArray<Integer> c = new CircularArray<Integer>();
		PrintStream cout = System.out;

		c.add(3);
		c.add(4);
		cout.println(c.v);
		c.add(7);
		cout.println(c.v);
		c.rotate(2);
		c.add(12);
		c.add(25);
		cout.println(c.v);
		c.rotate(-1);
		c.add(77);
		cout.println(c.v);
		c.removeElementAt(2);
		cout.println(c.v);
		cout.println(c.elementAt(0));
	}
}