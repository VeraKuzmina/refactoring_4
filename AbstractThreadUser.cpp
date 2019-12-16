#include "AbstractThreadUser.h"
#include <fstream>
#include <mutex>

AbstractThreadUser::AbstractThreadUser(int n, int m, const char* a, const char* b, const char* d)
{
	this->n = n;
	this->m = m;
	A = new int[n];
	B = new int[m];
	D = new int[m + n];
	for (int i = 0; i < n; i++)
		A[i] = NULL;
	for (int i = 0; i < m; i++)
		B[i] = NULL;
	for (int i = 0; i < m+n; i++)
		D[i] = NULL;
	af = a;
	bf = b;
	df = d;
}

AbstractThreadUser::~AbstractThreadUser() 
{
	delete[] A;
	delete[] B;
	delete[] D;
}

void AbstractThreadUser::generateRandomArray(int &i, int* Arr)
{
	int aNext;
	bool fl = true;
	while (fl) {
		aNext = rand() % 11 + 1;
		fl = false;
		for (int j = 0; j < i; j++)
		if (Arr[j] == aNext)
			fl = true;
	}
	Arr[i] = aNext;
}

int AbstractThreadUser::createArrayD(int i, int* A, int* B, int* D, int n, int &k)
{
	if (A[i] != NULL && i != n) {
		bool fl = false;
		int r = 0;
		while (B[r] && r<n) {
			if (B[r] == A[i])
				fl = true;
			r++;
		}
		for (int l = 0; l < k; l++)
			if (D[l] == A[i])
				fl = false;
		if (fl)
			D[k++] = A[i];
		i++;
	}
	return i;
}