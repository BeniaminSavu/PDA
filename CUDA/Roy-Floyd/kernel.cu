#include <stddef.h>
#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


#define N 6


__global__ void RoyFloyd(int a[N][N], int k)
{
	int i = threadIdx.x;
	int j = threadIdx.y;

	if (a[i][j] > a[i][k] + a[k][j])
		a[i][j] = a[i][k] + a[k][j];
}

int main()
{
	int h_a[N][N] = {
		{ 0, 2, 5, 999, 999, 999 },
		{ 999, 0, 7, 1, 99 , 8 },
		{ 999, 999, 0, 4, 999, 999 },
		{ 999, 999, 999, 0, 3, 999 },
		{ 999, 999, 2, 999, 0, 3 },
		{ 999, 5, 999, 2, 4, 0 }
	};
	size_t size = N * sizeof(int);
	int *d_a;
	int *d_k;
	cudaMalloc(&d_a, size);
	cudaMalloc(&d_k, sizeof(int));

	int numBlocks = 1;
	dim3 threadsPerBlock(N, N);
	cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
	for (int k = 0; k < N; k++) {
		cudaMemcpy(d_k, &k, sizeof(int), cudaMemcpyHostToDevice);
		RoyFloyd <<<numBlocks, threadsPerBlock >>> (d_a, d_k);
	}
	cudaMemcpy(h_a, d_a, size, cudaMemcpyDeviceToHost);
	cudaFree(d_a);
	cudaFree(d_k);
    return 0;
}

