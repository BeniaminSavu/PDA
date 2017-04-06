#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 32
#define PROCCESSES 4

int main(int argc, char *argv[])
{
	int numprocs, rank;
	int positions[SIZE] = { 0 };
	int localPositions[SIZE / PROCCESSES] = { 0 };
	int elements[SIZE] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,10,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32 };
	int localElements[SIZE / PROCCESSES];
	int elementToFind = 10;
	int found = 0;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	

	MPI_Scatter(elements, SIZE/PROCCESSES, MPI_INT, localElements, SIZE / PROCCESSES, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < SIZE / PROCCESSES; i++)
	{
		if (localElements[i] == elementToFind)
		{
			localPositions[i] = i + (rank*SIZE/PROCCESSES);
		}
		else
		{
			localPositions[i] = -1;
		}
	}
	MPI_Gather(localPositions, SIZE/PROCCESSES, MPI_INT, positions, SIZE/PROCCESSES, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		for (i = 0; i < SIZE; i++)
		{
			if (positions[i] > 0) {
				printf("%d ", positions[i]);
				found = 1;
			}
		}
		if (!found)
			printf("Not Found !");
	}
	MPI_Finalize();
}
