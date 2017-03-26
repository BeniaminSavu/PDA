#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 30

int main(int argc, char *argv[])
{
	int numprocs, rank;
	int elements[SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
	int elementToFind = 100;
	int found = 0;
	int message = 0;
	int i;
	MPI_Status status;
	MPI_Request req;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
	
	for (i = rank; i < SIZE; i = i + numprocs)
	{
		if(elements[i] == elementToFind)
		{
			printf("%d ", i);
			found = 1;
		}
	}
	MPI_Isend(&found, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,&req);

	if (rank == 0) 
	{
		for (i = 0; i < numprocs; i++)
		{
			MPI_Recv(&message, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			if (message)
			{
				found = message;
			}
		}
		if (!found)
			printf("Not found");
	}
	
	MPI_Finalize();
}
