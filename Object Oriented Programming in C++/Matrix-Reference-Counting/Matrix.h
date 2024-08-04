#pragma once
#include <iostream>
#include <cstdlib>

class Matrix {
	struct rcMatrix;
	rcMatrix* data;

	public:
	// Exceptions
		class InvalidRange {};
		class InvalidSum {};
		class InvalidProduct {};
		class InvalidRead {};

	// Constructors and destructor
		Matrix();
		Matrix(size_t rows, size_t cols);
		Matrix(const Matrix& m);
		~Matrix();
	
	// Assignment operator
		Matrix& operator=(const Matrix& m);
		
	// Access operators
		class DoubleRef;
		double read(size_t row, size_t col) const;
		void write(size_t row, size_t col, double val);
		double operator()(size_t row, size_t col) const;
		DoubleRef operator()(size_t row, size_t col);
	
	// Display operator
		friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
	
	// Arithmetic operators
		Matrix operator+(const Matrix& m) const;
		Matrix& operator+=(const Matrix& m);
		Matrix operator-(const Matrix& m) const;
		Matrix& operator-=(const Matrix& m);
		Matrix operator*(const Matrix& m) const;
		Matrix& operator*=(const Matrix& m);

	// Logic operators
		bool operator==(const Matrix& m) const;
		bool operator!=(const Matrix& m) const;

	// Reading from input file stream
		friend std::istream& operator>>(std::istream& is, Matrix& m);
};

class Matrix::DoubleRef {
	friend class Matrix;
	Matrix& mat;
	size_t row, col;

	DoubleRef(Matrix& m, size_t r, size_t c) : mat(m), row(r), col(c) {};

	public:
		operator double() const 
		{
			return mat.read(row, col);
		}
		Matrix::DoubleRef& operator=(double d)
		{
			mat.write(row, col, d);
			return *this;
		}
		Matrix::DoubleRef& operator=(const DoubleRef& ref)
		{
			return operator=((double)ref);
		}
};

template <std::size_t Rows, std::size_t Cols>
Matrix processArray(double (&arr)[Rows][Cols])
{
	Matrix m(Rows, Cols);
	for (size_t i = 0; i < Rows; ++i) {
		for (size_t j = 0; j < Cols; ++j) {
			m.write(i, j, arr[i][j]);
		}
	}
	return m;
}

std::string* readText(std::istream& is, size_t& size);
void incrementSize(std::string* text, size_t& size);
size_t countTokens(std::string line, const char delim[]);
