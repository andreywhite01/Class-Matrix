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
	//����������� �� ����������
	Matrix();

	//����������� � ����������
	Matrix(const int& num_rows, const int& num_cols);

	//����������� �����������
	Matrix(const Matrix& matr);

	//����������
	~Matrix();

	//��������� ����������� �������
	pair<int, int> GetDim() const;

	//��������� �������� ������� ����� �������� ������� ��������
	bool SetValues(double* matr[], const int& n_rows, const int& n_cols);

	//��������� �������� ������� ����� ������ ������� �������� �� �����
	bool SetValues(const string& filename);

	//����������� ������ �� ������� �������
	double At(const int& row, const int& col) const;

	//���������� ��������� ����������//

	//������ �������� �� �������
	double* operator[](const int& row);

	//���������� ������� � ���������
	Matrix operator+=(const Matrix& rhs);

	//����������
	Matrix operator=(const Matrix& rhs);

	//���������������� �������
	Matrix operator!();

	//��������� ����
	friend istream& operator>>(istream& in, Matrix& matr);

	//��������� �����
	friend ostream& operator<<(ostream& out, const Matrix& matr);

	//�������� ������
	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);

	//�������� ������
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);

	//�������� ������
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

	//������������ ���������
	friend bool operator==(const Matrix& lhs, const Matrix& rhs);

private:
	int num_rows;
	int num_cols;
	double **matrix;
};
