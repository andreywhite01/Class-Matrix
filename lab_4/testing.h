#pragma once
#include "matrix.h"


template <class T1, class T2>
void Assert(const T1& left, const T2& right, string hint) {
	if (!(left == right))
		cerr << "Ошибка в тесте " << hint << ": " << left << " != " << right << endl;
	else
		cerr << "Тест " << hint << " is OK\n";
}
void Test();

