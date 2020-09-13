#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <assert.h>
#include <chrono>
#include  <Windows.h>

//Initialize the variables
int NUM_THREADS = 16;

long long N = 1500;

double** A, ** B, ** C;


// created a thread and assigned a threadID 
// sim computing matrix multiply
DWORD WINAPI MultiplyMultiplyMatrix(LPVOID lpThreadParameter) {

	
		int threadID = (int)lpThreadParameter;
		int itemPerThread = (N + NUM_THREADS-1) / NUM_THREADS; 
		int startIndex = itemPerThread * threadID;
		int endIndex =  min(startIndex + itemPerThread , N); 

		for(int i=startIndex; i<endIndex; i++)
				for (int j = 0; j < N; j++)
				{
					double total = 0;
					for (int k = 0; k < N; k++)
						total += A[i][k] * B[k][j];
					C[i][j] = total;
				}

	
	return 0;
}


// main funciton 
int main(int argc, char* argv[])
{
	
	

	A = new double* [N];
	B = new double* [N];
	C = new double* [N];

	srand(42);

	for (int i = 0; i < N; i++)
	{
		A[i] = new double[N];
		B[i] = new double[N];
		C[i] = new double[N];
		for (int j = 0; j < N; j++) {
			A[i][j] = rand();
			B[i][j] = rand();

		}
	}

	auto start_time = std::chrono::high_resolution_clock::now();


	HANDLE* handles = new HANDLE[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++)
	{

		handles[i] = CreateThread(NULL, 0, MultiplyMultiplyMatrix, (LPVOID)i, 0, NULL);
	}
	WaitForMultipleObjects(NUM_THREADS, handles, TRUE, INFINITE);
	

	auto end_time = std::chrono::high_resolution_clock::now();  
	std::chrono::duration<double> duration = end_time - start_time;
	printf("%f seconds \n", duration.count());



	return 0;
} 

