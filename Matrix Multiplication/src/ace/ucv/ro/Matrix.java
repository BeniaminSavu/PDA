package ace.ucv.ro;

import java.util.Random;

public class Matrix {
	private int lines;
	private int columns;
	private int matrix[][];
	private Random random = new Random();
	
	public Matrix(){
		
	}
	
	public Matrix(int lines, int columns){
		this.lines = lines;
		this.columns = columns;
		matrix = new int[lines][columns];
	}
	
	public void createMatrix(){
		for(int i=0;i<lines;i++){
			for(int j=0;j<columns;j++){
				setElement(i,j,random.nextInt(10));
			}
		}
	}
	
	public void display(){
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				System.out.print(getElement(i, j) + " ");
			}
			System.out.println();
		}
	}

	public int getLines() {
		return lines;
	}

	public int getColumns() {
		return columns;
	}
	
	public int getElement(int i, int j){
		return matrix[i][j];
	}
	
	public void setElement(int i, int j, int value){
		matrix[i][j] = value;
	}
}
