#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool isPrime(int number) 
{
	for (int i = 2; i <= sqrt(number); i++)
	{
		if (number % i == 0)
			return false;
	}

	return true;
}

int main(int argc, char *argv[])
{
	int numprocs, rank;
	int n = 1000;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
	
	for (i = 2 + rank; i < n; i = i + numprocs) {
		if (isPrime(i))
		{
			printf("%d ", i);
		}
	}
	printf("\n");
	MPI_Finalize();
}
