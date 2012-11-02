// InvertMatrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

double randomDouble(double min, double max);
VSLStreamStatePtr stream;
LARGE_INTEGER time1,time2,freq;

int _tmain(int argc, _TCHAR* argv[])
{
	QueryPerformanceFrequency(&freq);
	SYSTEMTIME t;
	GetLocalTime(&t);
	
	vslNewStream( & stream, VSL_BRNG_SFMT19937, t.wMilliseconds );


	int size = 2000;
	
	double * rand_matrix;
	double * rand_matrix_copy;
	double * identity;
	int * pivots;


	for(int i = 0; i < 5; i ++){

	 rand_matrix = new double[size*size];

	pivots = new int[size];
		for(int i = 0; i < size*size; i ++){
			rand_matrix[i] = randomDouble(0,1);
		}


	rand_matrix_copy = new double[size*size];
	memcpy(rand_matrix_copy, rand_matrix, sizeof(double)*size*size);


	identity = new double[size*size];
		for(int i = 0; i < size*size; i ++){
			identity[i] = 0;
		}

	  // stores times and CPU frequency for profiling
	
	QueryPerformanceCounter(&time1);

	LAPACKE_dgetrf(LAPACK_ROW_MAJOR, size, size, rand_matrix,size,pivots);
	LAPACKE_dgetri(LAPACK_ROW_MAJOR, size, rand_matrix, size, pivots);

	QueryPerformanceCounter(&time2);
	cout<<"Time to memcpy: "<<1000*(double)(time2.QuadPart-time1.QuadPart)/(freq.QuadPart)<<"ms"<<endl<<endl;
	}


	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size, size, size,1, rand_matrix, size, rand_matrix_copy, size, 0, identity, size);

	cout<<identity[0]<<" " <<identity[1] <<" " <<identity[size]<<" " <<identity[size+1]<<endl;

	int a;
	cin>>a;

	

	return 0;
}

double randomDouble(double min, double max){				//change this to return full aray: faster
	double randNum;
	 vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, 1, &randNum, min, max);
	return randNum;
}