package ace.ucv.ro;

import java.util.List;

public class Task implements Runnable{
	private List<Coord> coords;
	private Matrix a;
	private Matrix b;
	private Matrix c;
	
	public Task(List<Coord> coords, Matrix a, Matrix b, Matrix c){
		this.coords = coords;
		this.a = a;
		this.b = b;
		this.c = c;
	}
	
	@Override
	public void run() {
		for (Coord coord : coords) {
			int sum = 0;
			int i = coord.getLine();
			int j = coord.getColumn();
			for(int k = 0; k <a.getColumns(); k++){
				sum += a.getElement(i, k) * b.getElement(k, j);
			}
			c.setElement(i, j, sum);
		}
	}
}
