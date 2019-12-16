#pragma once
#include "AbstractThreadUser.h"
#include <windows.h>

class ThreadUser :
	public AbstractThreadUser
{
public:
	ThreadUser(int n, int m, const char* a, const char* b, const char* d);
	~ThreadUser();
	void FirstThread();
	void SecondThread();
	void MainProg();
private:
	HANDLE mtA = NULL;
	HANDLE mtB = NULL;
	static DWORD WINAPI createArray(CONST LPVOID par);
	HANDLE ath = NULL;
	HANDLE bth = NULL;
	
	struct info {
		info(HANDLE* mut, int* const Array, const char* const file, const int n)
		: mut(mut), Array(Array), file(file), n(n) {}
		HANDLE* mut;
		int* const Array;
		const char* const file;
		const int n;
	};	
};

