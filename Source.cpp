#include "AbstractThreadUser.h"
#include "ThreadUser.h"
#include <stdlib.h>
#include <iostream>
/*
Программа запускается с командной строкой, содержащей параметры – два целых числа M и N 
(при этом M<<N), главный поток создает два дочерних, в первом генерируется случайное
целочисленное множество A, мощностью N, во втором – аналогичное множество B, мощность M. 
В это время главный поток по мере генерации A и B формирует множество D, равное объединению A и B. 
Полученные множества вывести в файлы.
*/

int main(int argc, char* argv[]) 
{
	int n = 0, m = 0;

	if (argc != 3) {
		std::cerr << "Введите размерности массивов" << std::endl;
		return 1;
	}

	n = atoi(argv[1]);

	m = atoi(argv[2]);
	if (n <= 0 || m <= 0) {
		std::cerr << "Размерности массивов должны быть положительныи числами" << std::endl;
		return 1;
	}
	AbstractThreadUser *tu;	
	tu = new ThreadUser(n, m, "a.txt", "b.txt", "d.txt");
	tu->FirstThread();
	tu->SecondThread();
	tu->MainProg();
	delete tu;
	return 0;
}
