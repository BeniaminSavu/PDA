#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 32

int main(int argc, char *argv[])
{
	int numprocs, rank;
	int elements[SIZE];
	int elementToFind = 1;
	int localMaxPos=-1;
	int maxPos = -1;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


	if (rank == 0)
	{
		for (i = 0; i < SIZE; i++)
		{
			elements[i] = i+1;
		}
	}

	MPI_Bcast(elements, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	for (i = rank; i < SIZE; i = i + numprocs)
	{
		if (elements[i] == elementToFind)
		{
			localMaxPos = i;
		}
	}

	MPI_Reduce(&localMaxPos, &maxPos, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		if (maxPos == -1)
			printf("Not found");
		else
			printf("The maximum position is %d", maxPos);
	}

	MPI_Finalize();
}
