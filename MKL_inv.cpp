#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <mkl_lapacke.h>
#include <cstring>
using namespace std;

//extern void print_matrix(char* desc, MKL_INT m, MKL_INT n, double* a, MKL_INT lda);
//extern void print_int_vector(char* desc, MKL_INT n, MKL_INT* a);
void MKL_inv(float* pDst,float* pSrc, int dim)
{
	int nRetVal = 0;
	int* ipiv = new int[dim * dim];
	//double* pSrcBak = new double[dim * dim];  // LAPACKE_sgesv�Ḳ��A���������pSrc����
	//memcpy(pSrcBak, pSrc, sizeof(double) * dim * dim);

	//memset(pDst, 0, sizeof(double) * dim * dim);
	for (int i = 0; i < dim; ++i)
	{
		// LAPACKE_sgesv��������AX=B����BΪ��λ����ʱ��XΪinv(A)
		pDst[i * (dim + 1)] = 1.0f;
	} 

	// ����LAPACKE_sgesv�󣬻Ὣinv(A)���ǵ�X����pDst����/////////////////////////////////////////////////
	nRetVal = LAPACKE_sgesv(102, dim, dim, pSrc, dim, ipiv, pDst, dim);
	int aaaa = nRetVal;
	delete[] ipiv;
	ipiv = nullptr;

	//delete[] pSrcBak;
	//pSrcBak = nullptr;

	//return nRetVal;
}