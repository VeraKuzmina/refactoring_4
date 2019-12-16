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
	info* infoA = new info(&mtA, A, af, n);
	ath = CreateThread(NULL, 0, generateArr, infoA, 0, NULL);
}

void ThreadUser::SecondThread()
{
	info* infoB = new info(&mtB, B, bf, m);
	bth = CreateThread(NULL, 0, generateArr, infoB, 0, NULL);
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
		i = createArrayD(i, A, B, D, n, k);
		ReleaseMutex(mtA);
		WaitForSingleObject(mtB, INFINITE);
		j = createArrayD(j, B, A, D, m, k);
		ReleaseMutex(mtB);
	}
	for (int l = 0; l < k; l++)
		dff << D[l] << " ";
	dff.close();
}

DWORD WINAPI ThreadUser::createArray(CONST LPVOID par)
{
	info* infoD = (info*)par;
	HANDLE *mut = infoD->mut;
	int* const Array = infoD->Array;
	const char* const file = infoD->file;
	const int n = infoD->n;
	
	ofstream aff(file);

	srand(time(0) + n);
	for (int i = 0; i < n; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		generateRandomArray(i, Array);
		ReleaseMutex(mut);
	}
	for (int i = 0; i < n; i++)
		aff << Array[i] << " ";
	aff.close();
	return 0;
}
