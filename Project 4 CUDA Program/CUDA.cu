#include <stdio.h>

#define N 512
#define BLOCK_SIZE 32

__global__ 
void matrix_multiplication(int *A, int *B, int *C)
{
	// Block row and column
	int blockX = blockIdx.x;
	int blockY = blockIdx.y;
	// Thread row and column
	int threadX = threadIdx.x;
	int threadY = threadIdx.y;
	
	// The row and column of the result matrix
	int row = blockY * BLOCK_SIZE + threadY;
	int col = blockX * BLOCK_SIZE + threadX;
	
	// local variable to compute result
	int sum = 0;

	__shared__ int tempA[BLOCK_SIZE][BLOCK_SIZE];
	__shared__ int tempB[BLOCK_SIZE][BLOCK_SIZE];
	
	// i stands for i-th block
	for (int i = 0; i < (N / BLOCK_SIZE); i++)
	{
		tempA[threadY][threadX] = A[row * N + i * BLOCK_SIZE + threadX];
		tempB[threadY][threadX] = B[(i * BLOCK_SIZE + threadY) * N + col];
		__syncthreads();

		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			sum += tempA[threadY][j] * tempB[j][threadX];
		}
		__syncthreads();

	}
	
	// Each thread compute an element of result matrix C
	C[row * N + col] = sum;
}

// Print result
void print_matrix(int *a)
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf("%d ", a[i * N + j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	int *a, *b, *c; //host copy of a, b, c
	int *dev_a, *dev_b, *dev_c; // device copy of a, b, c
	int size = N * N * sizeof( int );
	
	a = ( int* ) malloc(size);
	b = ( int* ) malloc(size);
	c = ( int* ) malloc(size);


	//allocate device copies of a, b
	cudaMalloc( ( void** ) &dev_a, size	);
	cudaMalloc( ( void** ) &dev_b, size );
	cudaMalloc( ( void** ) &dev_c, size );


	// initialize host copies
	for( int i = 0; i < N * N; ++i)
	{
		a[i] = rand( ) % 100;
		b[i] = rand( ) % 100;
	}

	// copy inputs to device
	cudaMemcpy( dev_a, a, size, cudaMemcpyHostToDevice );
	cudaMemcpy( dev_b, b, size, cudaMemcpyHostToDevice );

	// block size and number of threads within a block
	dim3 dimGrid( (N / BLOCK_SIZE),(N / BLOCK_SIZE),1);
	dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE,1);

	// launch kernel function on GPU, passing parameters
	matrix_multiplication<<< dimGrid, dimBlock>>>( dev_a, dev_b, dev_c);

	cudaMemcpy( c, dev_c, size, cudaMemcpyDeviceToHost);

	print_matrix(a);
	print_matrix(b);
	print_matrix(c);


	free(a);
	free(b);
	free(c);
	
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	return 0;
}
