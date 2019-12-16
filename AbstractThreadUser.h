#pragma once
#define NULL 0
#include <fstream>
#include <mutex>

class AbstractThreadUser
{
public:
	AbstractThreadUser(int n, int m, const char* a, const char* b, const char* d);
	~AbstractThreadUser();
	virtual void FirstThread() = 0;
	virtual void SecondThread() = 0;
	virtual void MainProg() = 0;
	void static generateRandomArray(int &i, int* A);
	int static createArrayD(int i, int* A, int* B, int* D, int n, int &k);
protected:
	int n;
	int m;
	int *A;
	int *B;
	int *D;
	const char *af;
	const char *bf;
	const char *df;
};

