package ace.ucv.ro;

import java.util.LinkedList;
import java.util.List;

public class Main {

	public static final int NO_PRODUCERS = 5;
	public static final int NO_CONSUMERS = 10;

	public static void main(String args[]) {
		
		List<Integer> sharedQueue = new LinkedList<Integer>();
		Object queueFull = new Object();
		Object queueEmpty = new Object();

		Producer[] producer = new Producer[NO_PRODUCERS];
		Thread producerThread[] = new Thread[NO_PRODUCERS];
		Consumer[] consumer = new Consumer[NO_CONSUMERS];
		Thread consumerThread[] = new Thread[NO_CONSUMERS];

		for (int i = 0; i < NO_PRODUCERS; i++) {
			producer[i] = new Producer(sharedQueue, queueFull, queueEmpty);
			producerThread[i] = new Thread(producer[i]);
			producerThread[i].start();
		}
		for (int i = 0; i < NO_CONSUMERS; i++) {
			consumer[i] = new Consumer(sharedQueue, queueFull, queueEmpty);
			consumerThread[i] = new Thread(consumer[i]);
			consumerThread[i].start();
		}

	}
}
