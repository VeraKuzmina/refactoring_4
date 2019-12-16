#include "ThreadUser.h"
#include <time.h>

using namespace std;

ThreadUser::ThreadUser(int n, int m, const char* a, const char* b, const char* d):AbstractThreadUser(n,m,a,b,d)
{
	mtA = CreateMutex(NULL, FALSE, NULL);
	mtB = CreateMutex(NULL, FALSE, NULL);
}

ThreadUser::~ThreadUser()
{
	CloseHandle(mtA);
	CloseHandle(mtB);
}

void ThreadUser::FirstThread()
{
	void** args = new void*[4];
	*args = &mtA;
	*(args + 1) = A;
	*(args + 2) = af;
	*(args + 3) = &n;
	ath = CreateThread(NULL, 0, generate, args, 0, NULL);
}

void ThreadUser::SecondThread()
{
	void** args = new void*[4];
	*args = &mtB;
	*(args + 1) = B;
	*(args + 2) = bf;
	*(args + 3) = &m;
	bth = CreateThread(NULL, 0, generate, args, 0, NULL);
}

void ThreadUser::MainProg()
{
	ofstream dff(df);
	int i = 0;
	int j = 0;
	int k = 0;
	while ((i+j) < (m+n))
	{
		WaitForSingleObject(mtA, INFINITE);
		i = arrayD(i, A, B, D, n, k);
		ReleaseMutex(mtA);
		WaitForSingleObject(mtB, INFINITE);
		j = arrayD(j, B, A, D, m, k);
		ReleaseMutex(mtB);
	}
	for (int l = 0; l < k; l++)
		dff << D[l] << " ";
	dff.close();
}

DWORD WINAPI ThreadUser::generate(CONST LPVOID par)
{
	HANDLE mut = * (void**)par;
	int* Array = (int *) *((void**)par + 1);
	char* file = (char *)*((void**)par + 2);
	
	int *nn = (int *) *((void**)par + 3);
	int n = *nn;

	ofstream aff(file);

	srand(time(0) + n);
	for (int i = 0; i < n; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		creationArray(i, Array);
		ReleaseMutex(mut);
	}
	for (int i = 0; i < n; i++)
		aff << Array[i] << " ";
	aff.close();
	return 0;
}
