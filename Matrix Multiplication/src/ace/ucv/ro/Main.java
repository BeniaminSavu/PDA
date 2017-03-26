package ace.ucv.ro;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

	private static final int A_MATRIX_LINES = 3;
	private static final int A_MATRIX_COLUMNS = 5;
	private static final int B_MATRIX_LINES = 5;
	private static final int B_MATRIX_COLUMNS = 2;
	private static final int MAXIMUM_NUMBER_OF_TASKS = 3;
	private static final int THREADS = 4;

	public static void main(String[] args) {
		ExecutorService executorService = Executors.newFixedThreadPool(THREADS);
		List<Coord> coords = new ArrayList<Coord>();
		List<Task> tasks;

		Matrix a = new Matrix(A_MATRIX_LINES, A_MATRIX_COLUMNS);
		Matrix b = new Matrix(B_MATRIX_LINES, B_MATRIX_COLUMNS);
		Matrix c = new Matrix(a.getLines(), b.getColumns());

		a.createMatrix();
		b.createMatrix();
		tasks = createTasks(coords, a, b, c);

		while (!tasks.isEmpty()) {
			executorService.execute(tasks.remove(0));
		}
		executorService.shutdown();
		a.display();
		System.out.println();
		b.display();
		System.out.println();
		c.display();

	}

	private static List<Task> createTasks(List<Coord> coords, Matrix a, Matrix b, Matrix c) {
		int taskNumber = 0;
		List<Task> tasks = new LinkedList<Task>();
		for (int i = 0; i < c.getLines(); i++) {
			for (int j = 0; j < c.getColumns(); j++) {
				Coord coord = new Coord(i, j);
				coords.add(taskNumber % MAXIMUM_NUMBER_OF_TASKS, coord);
				taskNumber++;
				if (taskNumber == MAXIMUM_NUMBER_OF_TASKS) {
					tasks.add(new Task(coords, a, b, c));
					taskNumber = 0;
				}
			}

		}
		return tasks;
	}

}
