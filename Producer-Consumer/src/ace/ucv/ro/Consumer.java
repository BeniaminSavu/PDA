package ace.ucv.ro;

import java.util.List;

public class Consumer implements Runnable {
	private List<Integer> sharedQueue;
	private Object queueFull;
	private Object queueEmpty;

	public Consumer(List<Integer> sharedQueue, Object queueFull, Object queueEmpty) {
		this.sharedQueue = sharedQueue;
		this.queueFull = queueFull;
		this.queueEmpty = queueEmpty;
	}

	@Override
	public void run() {

		try {
			consume();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

	private void consume() throws InterruptedException {
		Thread.sleep(200);
		synchronized (queueFull) {
			while (sharedQueue.size() == 0) {
				System.out.println("COADA ESTE GOALA");
				queueFull.wait();
			}
			System.out.println("CONSUMAT : " + sharedQueue.remove(0));
		}
		
		
		synchronized (queueEmpty) {
			queueEmpty.notify();
		}
	}

}
