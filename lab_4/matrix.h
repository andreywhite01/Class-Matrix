#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

bool is_equal(double x, double y);

class Matrix
{
public:
	//конструктор по умолячанию
	Matrix();

	//конструктор с параметром
	Matrix(const int& num_rows, const int& num_cols);

	//конструктор копирования
	Matrix(const Matrix& matr);

	//деструктор
	~Matrix();

	//получение размерности матрицы
	pair<int, int> GetDim() const;

	//уставнока значений матрицы путем передачи массива значений
	bool SetValues(double* matr[], const int& n_rows, const int& n_cols);

	//уставнока значений матрицы путем чтения массива значений из файла
	bool SetValues(const string& filename);

	//возвращение ссылки на элемент матрицы
	double At(const int& row, const int& col) const;

	//Перегрузим несколько операторов//

	//поиска элемента по индексу
	double* operator[](const int& row);

	//добавление матрицы к имеющейся
	Matrix operator+=(const Matrix& rhs);

	//присовение
	Matrix operator=(const Matrix& rhs);

	//транспонирование матрицы
	Matrix operator!();

	//потоковый ввод
	friend istream& operator>>(istream& in, Matrix& matr);

	//потоковый вывод
	friend ostream& operator<<(ostream& out, const Matrix& matr);

	//сложение матриц
	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);

	//разность матриц
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);

	//разность матриц
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

	//поэлементное сравнение
	friend bool operator==(const Matrix& lhs, const Matrix& rhs);

private:
	int num_rows;
	int num_cols;
	double **matrix;
};
