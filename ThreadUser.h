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
	static DWORD WINAPI generate(CONST LPVOID par);
	HANDLE ath = NULL;
	HANDLE bth = NULL;
};

