
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <math.h>
#include <stdio.h>

void saveBmp(char* filename, unsigned char *image, int width, int height){
	FILE* f = fopen("test.bmp", "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	fclose(f);
	
	f = fopen(filename, "wb");
	fwrite(info, sizeof(unsigned char), 54, f);
	unsigned char tmp;

	int size = 3 * width * height;
	unsigned char *data = new unsigned char[size];
	for (int i = 0, k=0; i < size; i+=3, k++){
		data[i] = data[i + 1] = data[i + 2] = image[k];
	}
	fwrite(data, sizeof(unsigned char), size, f);
	fclose(f);
}

unsigned char* readBMP(char* filename, int *width, int *height)
{
	FILE* f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	*width= *(int*)&info[18];
	*height = *(int*)&info[22];

	int size = 3 * (*width) * (*height);
	unsigned char *data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	int size2 = *width * (*height);
	unsigned char *redCol = new unsigned char[size2];
	int k = 0;
	for (int i = 2; i < size; i += 3){
		redCol[k] = data[i];
		k++;
	}

	return redCol;
}

__global__ void edgeDetection(unsigned char *data, unsigned char *newData, int *width, int *height)
{
	int pixelMatrix[3][3];
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	
	int row = i / (*width);
	int col = i % (*width);

	if (row > 0 && row < *height - 1 && col>0 && col < *width - 1){
		pixelMatrix[0][0] = data[(row - 1) * (*width) + col - 1];
		pixelMatrix[0][1] = data[(row - 1) * (*width) + col];
		pixelMatrix[0][2] = data[(row - 1) * (*width) + col + 1];
		pixelMatrix[1][0] = data[row * (*width) + col - 1];
		pixelMatrix[1][2] = data[row * (*width) + col + 1];
		pixelMatrix[2][0] = data[(row + 1) * (*width) + col - 1];
		pixelMatrix[2][1] = data[(row + 1) * (*width) + col];
		pixelMatrix[2][2] = data[(row + 1) * (*width) + col + 1];

		double gy = pixelMatrix[0][0] * (-1) + pixelMatrix[0][1] * (-2) + pixelMatrix[0][2] * (-1) + pixelMatrix[2][0] + pixelMatrix[2][1] * 2 + pixelMatrix[2][2] * 1;
		double gx = pixelMatrix[0][0] + pixelMatrix[0][2] * (-1) + pixelMatrix[1][0] * 2 + pixelMatrix[1][2] * (-2) + pixelMatrix[2][0] + pixelMatrix[2][2] * (-1);
		int gradient = (int)sqrt(gy*gy + gx*gx);

		newData[i] = gradient;
	}else {
		newData[i] = 0;
	}

}

int main()
{	
	int width, height;
	unsigned char *h_data = readBMP("test.bmp", &width, &height);
	
	unsigned char *d_data = 0;
	unsigned char *d_newData = 0;
	int *d_width;
	int *d_height;

	size_t size = height * width;
	unsigned char *h_newData = new unsigned char[size];
	
	cudaSetDevice(0);
	cudaMalloc(&d_data, size);
	cudaMalloc(&d_width, sizeof(int));
	cudaMalloc(&d_height, sizeof(int));
	cudaMalloc(&d_newData, size * sizeof(unsigned char));
	cudaMemcpy(d_data, h_data, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_width, &width, sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_height, &height, sizeof(int), cudaMemcpyHostToDevice);

	edgeDetection << <width, height >> >(d_data, d_newData, d_width, d_height);
	cudaDeviceSynchronize();
	cudaMemcpy(h_newData, d_newData, size, cudaMemcpyDeviceToHost);

	

	saveBmp("test2.bmp", h_newData, width, height);
    return 0;
}

