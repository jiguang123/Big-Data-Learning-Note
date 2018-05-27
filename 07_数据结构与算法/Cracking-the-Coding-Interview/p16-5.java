// 16.5 There're three methods in a class FooBar, how would you make sure that they're executed in a fixed order, in whichever order they're called?
public class FirstRun implements Runnable {
	private FooBar fooBar;
	
	public FirstRun(FooBar fooBar) {
		// TODO Auto-generated constructor stub
		this.fooBar = fooBar;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		fooBar.first();
	}
}

// -----------------------------------------------------------------------------
public class SecondRun implements Runnable {
	private FooBar fooBar;
	
	public SecondRun(FooBar fooBar) {
		// TODO Auto-generated constructor stub
		this.fooBar = fooBar;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		fooBar.second();
	}
}

// -----------------------------------------------------------------------------
public class ThirdRun implements Runnable {
	private FooBar fooBar;
	
	public ThirdRun(FooBar fooBar) {
		// TODO Auto-generated constructor stub
		this.fooBar = fooBar;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		fooBar.third();
	}
}

// -----------------------------------------------------------------------------
import java.util.concurrent.Semaphore;

public class FooBar {
	private Semaphore sem1;
	private Semaphore sem2;
	private Semaphore sem3;
	
	public FooBar() {
		// TODO Auto-generated constructor stub
		sem1 = new Semaphore(1);
		sem2 = new Semaphore(1);
		sem3 = new Semaphore(1);
		
		try {
			sem1.acquire();
			sem2.acquire();
			sem3.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void first() {
		System.out.println("first");
		
		sem1.release();
	}

	public void second() {
		try {
			sem1.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sem1.release();
		System.out.println("second");
		sem2.release();
	}

	public void third() {
		try {
			sem2.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sem2.release();
		System.out.println("third");
		sem3.release();
	}

	public static void main(String[] args) {
		FooBar fooBar = new FooBar();
		Thread t1 = new Thread(new FirstRun(fooBar));
		Thread t2 = new Thread(new SecondRun(fooBar));
		Thread t3 = new Thread(new ThirdRun(fooBar));
		
		t3.start();
		t1.start();
		t2.start();
	}
}
