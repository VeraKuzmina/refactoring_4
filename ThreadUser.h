#pragma once
#include "AbstractThreadUser.h"
#include <mutex>
#include <thread>
#include <string>

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
	std::mutex mtA;
	std::mutex mtB;
	void static arrayCreation(int n, const char* af, int* A, std::mutex &mtA);
	std::thread* ath;
	std::thread* bth;
};

