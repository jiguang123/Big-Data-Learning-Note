// This is the class for chopsticks.
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Chopstick {
	private Lock lock;
	
	public Chopstick() {
		lock = new ReentrantLock();
	}
	
	public boolean pickUp() {
		return lock.tryLock();
	}
	
	public void putDown() {
		lock.unlock();
	}
}

//------------------------------------I'm a delimiter------------------------------------
// This is the class for philosophers.
import java.util.Vector;

public class Philosopher extends Thread {
	private Chopstick left;
	private Chopstick right;
	private int id;
	int appetite;

	final int FULL_APPETITE = 10;

	public Philosopher(Chopstick left, Chopstick right, int id) {
		// TODO Auto-generated constructor stub
		appetite = 0;
		this.left = left;
		this.right = right;
		this.id = id;
	}

	private boolean pickUp() {
		if (!left.pickUp()) {
			return false;
		}
		if (!right.pickUp()) {
			left.putDown();
			return false;
		}
		return true;
	}

	private void putDown() {
		left.putDown();
		right.putDown();
	}

	public boolean eat() {
		while (appetite < FULL_APPETITE) {
			if (!pickUp()) {
				return false;
			}
			System.out.println(id + ":chew~");
			++appetite;
			putDown();
		}
		return appetite == FULL_APPETITE;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		super.run();
		while (!eat()) {
			// Not full yet.
		}
	}

	public static void main(String[] args) {
		final int n = 6;
		Vector<Chopstick> chopsticks = new Vector<Chopstick>();
		Vector<Philosopher> philosophers = new Vector<Philosopher>();

		for (int i = 0; i < n; ++i) {
			chopsticks.add(new Chopstick());
		}
		for (int i = 0; i < n; ++i) {
			philosophers.add(new Philosopher(chopsticks.elementAt(i),
					chopsticks.elementAt((i + 1) % n), i + 1));
		}
		
		for (int i = 0; i < n; ++i) {
			philosophers.elementAt(i).start();
		}
	}
}
