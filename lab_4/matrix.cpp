#include "matrix.h"

bool is_equal(double x, double y) {
	return fabs(x - y) < numeric_limits<double>::epsilon();
}

Matrix::Matrix() : num_rows(0), num_cols(0) {
//	cout << "Вызван конструктор по умолчанию\n";
	matrix = new double* [0];
}

Matrix::Matrix(const int& num_rows_, const int& num_cols_) : num_rows(num_rows_), num_cols(num_cols_) {
//	cout << "Вызван конструктор c параметром\n";
	matrix = new double* [num_rows];
	for (int i = 0; i < num_rows; ++i) {
		matrix[i] = new double[num_cols];
	}
}

Matrix::Matrix(const Matrix& matr) : num_rows(matr.GetDim().first), num_cols(matr.GetDim().second) {
//	cout << "Вызван конструктор копирования\n";
	matrix = new double* [num_rows];
	for (int row = 0; row < num_rows; ++row) {
		matrix[row] = new double[num_cols];
		for (int col = 0; col < num_cols; ++col) {
			matrix[row][col] = matr.matrix[row][col];
		}
	}
}

Matrix::~Matrix() {
//	cout << "Вызван деструктор\n";
	for (int i = 0; i < num_rows; ++i)
		delete matrix[i];
}

pair<int,int> Matrix::GetDim() const {
	return { num_rows, num_cols };
}

bool Matrix::SetValues(double* matr[], const int& n_rows, const int& n_cols) {
	
	//проверяем, что число строк или столбцов в массиве не равно нулю
	if (n_rows == 0 or n_cols == 0)
		return false;

	//если всё ок, изменяем размерность матрицы и инициализируем ее

	this->num_rows = n_rows;
	this->num_cols = n_cols;

	matrix = new double* [num_rows];
	for (int row = 0; row < num_rows; ++row) {
		matrix[row] = new double[num_cols];
		for (int col = 0; col < num_cols; ++col) {
			matrix[row][col] = matr[row][col];
		}
	}
	return true;
}

bool Matrix::SetValues(const string& filename) {
	ifstream in;
	in.open(filename);
	string line;

	//считаем количество строк и столбцов массива из файла
	set<int> set_num_cols;
	int n_rows = 0;
	while (getline(in, line,'\n')) {
		stringstream ss;
		ss << line;
		string str_val;

		n_rows++;
		int n_cols = 0;
		while (getline(ss, str_val, ' ')) {
			n_cols++;
		}
		set_num_cols.insert(n_cols);
	}

	//если число строк в массиве из файла не совподает с числом строк в матрице, то мы не сможем инициализировать матрицу
	if (n_rows != num_rows)
		return false;

	//если хотябы 2 строки имеют различный размер (или все строки имеют нулевую размерность), то инициализация матрицы невозможна
	if (set_num_cols.size() != 1)
		return false;

	int n_cols = (*set_num_cols.begin());

	//если число столбцов в файле не совпадает с числом столбцов в матрице, то инициализация матрицы невозможна
	if (n_cols != num_cols)
		return false;

	//если всё ок, инициализируем матрицу значениями из файла
	for (int row = 0; row < num_rows; ++row) {
		for (int col = 0; col < num_cols; ++col) {
			in >> matrix[row][col];
		}
	}
	return true;
}

double Matrix::At(const int& row, const int& col) const {
	return matrix[row][col];
}

double* Matrix::operator[](const int& row) {
	return matrix[row];
}

Matrix Matrix::operator+=(const Matrix& rhs) {
	//если размерности матриц не совпадают выводим ошибку и возвращаем пустую матрицу
	if (this->GetDim() != rhs.GetDim()) {
		cerr << "Невозможно найти сумму матриц (возвращена пустая матрица)/n";
		return Matrix();
	}

	Matrix res_matr(num_rows, num_cols);
	for (int row = 0; row < num_rows; ++row) {
		for (int col = 0; col < num_cols; ++col) {
			(this->matrix[row][col]) += rhs.matrix[row][col];
		}
	}
	return *this;
}

Matrix Matrix::operator=(const Matrix& rhs) {
	//меняем размерность матрицы на новую
	this->num_rows = rhs.num_rows;
	this->num_cols = rhs.num_cols;

	for (int row = 0; row < this->num_rows; ++row) {
		for (int col = 0; col < this->num_rows; ++col) {
			this->matrix[row][col] = rhs.At(row, col);
		}
	}
	return *this;
}

Matrix Matrix::operator!() {
	Matrix transpose_matrix(this->num_cols, this->num_rows);

	//инициализируем транспонированную матрицу
	for (int row = 0; row < this->num_rows; ++row) {
		for (int col = 0; col < this->num_rows; ++col) {
			transpose_matrix[col][row] = this->matrix[row][col];
		}
	}
	return transpose_matrix;
}

istream& operator>>(istream& in, Matrix& matr) {
	for (int row = 0; row < matr.num_rows; ++row) {
		for (int col = 0; col < matr.num_cols; ++col) {
			in >> matr[row][col];
		}
	}
	return in;
}

ostream& operator<<(ostream& out, const Matrix& matr) {
	out << "[ ";
	for (int row = 0; row < matr.num_rows - 1; ++row) {
		out << "[ ";
		for (int col = 0; col < matr.num_cols - 1; ++col) {
			out << matr.At(row,col) << ", ";
		}
		out << matr.At(row, matr.num_cols - 1) << " ], ";
	}

	out << "[ ";
	for (int col = 0; col < matr.num_cols - 1; ++col) {
		out << matr.At(matr.num_rows - 1, col) << ", ";
	}
	out << matr.At(matr.num_rows - 1, matr.num_cols - 1) << " ] ]";
	return out;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	//если размерности матриц не совпадают выводим ошибку и возвращаем пустую матрицу
	if (lhs.GetDim() != rhs.GetDim()) {
		cerr << "Невозможно найти сумму матриц (возвращена пустая матрица)/n";
		return Matrix();
	}

	int n_rows = lhs.num_rows, n_cols = lhs.num_cols;

	Matrix res_matr(n_rows, n_cols);
	for (int row = 0; row < n_rows; ++row) {
		for (int col = 0; col < n_cols; ++col) {
			res_matr[row][col] = lhs.matrix[row][col] + rhs.matrix[row][col];
		}
	}
	return res_matr;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
	//если размерности матриц не совпадают выводим ошибку и возвращаем пустую матрицу
	if (lhs.GetDim() != rhs.GetDim()) {
		cerr << "Невозможно найти разность матриц (возвращена пустая матрица)/n";
		return Matrix();
	}

	int n_rows = lhs.num_rows, n_cols = lhs.num_cols;

	Matrix res_matr(n_rows, n_cols);
	for (int row = 0; row < n_rows; ++row) {
		for (int col = 0; col < n_cols; ++col) {
			res_matr[row][col] = lhs.matrix[row][col] - rhs.matrix[row][col];
		}
	}
	return res_matr;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	//если количество столбцов первой матрицы не равно количеству сторок во второй матрице выводим ошибку и возвращаем пустую матрицу
	if (lhs.GetDim().second != rhs.GetDim().first) {
		cerr << "Матрицы нельзя перемножить (возвращена пустая матрица)/n";
		return Matrix();
	}

	int lhs_n_rows = lhs.num_rows,
		lhs_n_cols = lhs.num_cols,
		rhs_n_rows = rhs.num_rows,
		rhs_n_cols = rhs.num_cols;

	Matrix res_matr(lhs_n_rows, rhs_n_cols);
	for (int lhs_row = 0; lhs_row < lhs_n_rows; ++lhs_row) {
		for (int rhs_col = 0; rhs_col < rhs_n_cols; ++rhs_col) {
			double sum = 0;
			for (int num = 0; num < rhs_n_rows; ++num) {
				sum += lhs.At(lhs_row, num) * rhs.At(num, rhs_col);
			}
			res_matr[lhs_row][rhs_col] = sum;
		}
	}
	return res_matr;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetDim() != rhs.GetDim())
		return false;

	for (int row = 0; row < lhs.num_rows; ++row) {
		for (int col = 0; col < lhs.num_cols; ++col) {
			if (!is_equal(lhs.At(row, col), rhs.At(row, col)))
				return false;
		}
	}
	return true;
}