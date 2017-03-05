package ace.ucv.ro;

import java.util.List;
import java.util.Random;

public class Producer implements Runnable {

	private List<Integer> sharedQueue;
	private Object queueFull;
	private Object queueEmpty;
	private Random random = new Random();
	private int maxSize = 3;

	public Producer(List<Integer> sharedQueue, Object queueFull, Object queueEmpty) {
		this.sharedQueue = sharedQueue;
		this.queueFull = queueFull;
		this.queueEmpty = queueEmpty;
	}

	@Override
	public void run() {

		try {
			for(int i=1; i<3; i++){
				produce();				
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

	private void produce() throws InterruptedException {
		Thread.sleep(100);
		int ob = random.nextInt(100);
		synchronized (queueEmpty) {
			while (sharedQueue.size() == maxSize) {
				System.out.println("COADA ESTE PLINA " + "");
				queueEmpty.wait();
			}
			sharedQueue.add(ob);
			System.out.println("PRODUS : " + ob);
		}
		

		synchronized (queueFull) {
			queueFull.notify();
		}
	}

}