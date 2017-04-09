#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_A_LINES 10
#define MATRIX_A_COLUMNS 7
#define MATRIX_B_LINES 7
#define MATRIX_B_COLUMNS 10

int main(int argc, char *argv[])
{
	int a[MATRIX_A_LINES][MATRIX_A_COLUMNS];
	int b[MATRIX_B_LINES][MATRIX_B_COLUMNS];
	int c[MATRIX_A_LINES][MATRIX_B_COLUMNS];
	int result[MATRIX_A_LINES][MATRIX_B_COLUMNS];
	int numprocs, rank;
	srand(time(NULL));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
	
	if (rank == 0)
	{
		for (int i = 0; i < MATRIX_A_LINES; i++)
			for (int j = 0; j < MATRIX_A_COLUMNS; j++)
				a[i][j] = rand() % 10 + 1;

		for (int i = 0; i < MATRIX_B_LINES; i++)
			for (int j = 0; j < MATRIX_B_COLUMNS; j++)
				b[i][j] = rand() % 10 + 1;
		
		for (int i = 0; i < MATRIX_A_LINES; i++)
			for (int j = 0; j < MATRIX_B_COLUMNS; j++)
				c[i][j] = 0;
	}

	MPI_Bcast(a, MATRIX_A_LINES*MATRIX_A_COLUMNS, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(b, MATRIX_B_LINES*MATRIX_B_COLUMNS, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(c, MATRIX_A_LINES*MATRIX_B_COLUMNS, MPI_INT, 0, MPI_COMM_WORLD);
	
		
	for (int k = rank; k < MATRIX_A_LINES; k = k + numprocs)
	{
		for (int j = 0; j < MATRIX_B_COLUMNS; j++)
		{
			for (int i = 0; i < MATRIX_A_COLUMNS; i++)
			{
				c[k][j] = c[k][j] + a[k][i] * b[i][j];
			}

		}
	}

	MPI_Reduce(c, result, MATRIX_A_LINES*MATRIX_B_COLUMNS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int i = 0; i < MATRIX_A_COLUMNS; i++)
		{
			for (int j = 0; j < MATRIX_B_COLUMNS; j++)
				printf("%d ", result[i][j]);
			printf("\n");
		}

	}
	MPI_Finalize();
}


