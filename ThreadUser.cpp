#include "ThreadUser.h"

using namespace std;

ThreadUser::ThreadUser(int n, int m, const char* a, const char* b, const char* d):AbstractThreadUser(n,m,a,b,d)
{}

ThreadUser::~ThreadUser()
{}

void ThreadUser::FirstThread()
{
	ath = new std::thread(arrayCreation, n, af, A, ref(mtA));
}

void ThreadUser::SecondThread()
{
	bth = new std::thread(arrayCreation, m, bf, B, ref(mtB));
}

void ThreadUser::MainProg()
{
	ofstream dff(df);
	int i = 0, j = 0, k = 0;
	while (i + j < m + n)
	{
		mtA.lock();
		i = createArrayD(i, A, B, D, n, k);
		mtA.unlock();
		mtB.lock();
		j = createArrayD(j, B, A, D, m, k);
		mtB.unlock();
	}
	for (int l = 0; l < k; l++)
		dff << D[l] << " ";
	dff.close();
	
	ath->join();
	bth->join();
	delete ath;
	delete bth;
}

void ThreadUser::arrayCreation(int n, const char* f, int* Arr, std::mutex & mt)
{
	ofstream aff(f);

	srand(time(0) + n);
	for (int i = 0; i < n; i++)
	{
		mt.lock();
		generateRandomArray(i, Array);
		mt.unlock();
		aff << Array[i] << " ";
	}		
	aff.close();
	return 0;
}
