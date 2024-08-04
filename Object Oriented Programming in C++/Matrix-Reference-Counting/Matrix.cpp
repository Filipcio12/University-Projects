#include "Matrix.h"
#include <cstring>

struct Matrix::rcMatrix {
	double** arr;
	size_t rows;
	size_t cols;
	size_t rc;
	
	rcMatrix()
	{
		rc = 1;
		rows = 0;
		cols = 0;
		arr = NULL;
	};
	
	rcMatrix(size_t rows, size_t cols)
	{
		rc = 1;
		this->rows = rows;
		this->cols = cols;
		arr = new double*[rows];
		
		for (size_t i = 0; i < rows; ++i) {
			arr[i] = new double[cols];
		}

		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				arr[i][j] = 0;
			}
		}
	};
	
	~rcMatrix()
	{
		for (size_t i = 0; i < rows; ++i) {
			delete[] arr[i];
		}
		delete[] arr;
	};
	
	rcMatrix* detach()
	{
		if (rc == 1) {
			return this;
		}
		rcMatrix* m = new rcMatrix(rows, cols);
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				m->arr[i][j] = arr[i][j];
			}
		}
		rc--;
		return m;
	};
	
	private:
		rcMatrix(const rcMatrix&) = delete;
		rcMatrix& operator=(const rcMatrix&) = delete;
};

Matrix::Matrix()
{
	data = new rcMatrix();
}

Matrix::Matrix(size_t rows, size_t cols)
{
	data = new rcMatrix(rows, cols);
}

Matrix::Matrix(const Matrix& m)
{
	m.data->rc++;
	data = m.data;
}

Matrix::~Matrix()
{
	if (--data->rc == 0) {
		delete data;
	}
}

Matrix& Matrix::operator=(const Matrix& m)
{
	if (--data->rc == 0) {
		delete data;
	}
	m.data->rc++;
	data = m.data;
	return *this;
}

double Matrix::read(size_t row, size_t col) const
{
	if (data->rows > row && data->cols > col) {
		return data->arr[row][col];
	} else {
		throw InvalidRange();
	}
}

void Matrix::write(size_t row, size_t col, double val)
{
	if (data->rows > row && data->cols > col) {
		data = data->detach();
		data->arr[row][col] = val;
	} else {
		throw InvalidRange();
	}
}

double Matrix::operator()(size_t row, size_t col) const
{
	if (data->rows > row && data->cols > col) {
		return data->arr[row][col];
	} else {
		throw InvalidRange();
	}
}

Matrix::DoubleRef Matrix::operator()(size_t row, size_t col)
{
	if (data->rows > row && data->cols > col) {
		return DoubleRef(*this, row, col);
	} else {
		throw InvalidRange();
	}
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{	
	for (size_t i = 0; i < m.data->rows; ++i) {
        for (size_t j = 0; j < m.data->cols; ++j) {
            os << m(i, j) << "\t";
        }
        os << "\n";
    }
    return os;
}

Matrix Matrix::operator+(const Matrix& m) const
{
	if (data->rows != m.data->rows || data->cols != m.data->cols) {
		throw InvalidSum();
	}

	Matrix sum = *this;
	for (size_t i = 0; i < data->rows; ++i) {
        for (size_t j = 0; j < data->cols; ++j) {
            sum(i, j) =  sum(i, j) + m(i, j);
        }
    }
    return sum;
}

Matrix& Matrix::operator+=(const Matrix& m) 
{
	if (data->rows != m.data->rows || data->cols != m.data->cols) {
        throw InvalidSum();
    }
    for (size_t i = 0; i < data->rows; ++i) {
        for (size_t j = 0; j < data->cols; ++j) {
            data->arr[i][j] += m(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix& m) const
{
	if (data->rows != m.data->rows || data->cols != m.data->cols) {
		throw InvalidSum();
	}

	Matrix diff = *this;
	for (size_t i = 0; i < data->rows; ++i) {
        for (size_t j = 0; j < data->cols; ++j) {
            diff(i, j) = diff(i, j) - m(i, j);
        }
    }
    return diff;
}

Matrix& Matrix::operator-=(const Matrix& m) 
{
	if (data->rows != m.data->rows || data->cols != m.data->cols) {
        throw InvalidSum();
    }
    for (size_t i = 0; i < data->rows; ++i) {
        for (size_t j = 0; j < data->cols; ++j) {
            data->arr[i][j] -= m(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& m) const
{
    if (data->cols != m.data->rows) {
        throw InvalidProduct();
    }
    Matrix prod(data->rows, m.data->cols);
    for (size_t i = 0; i < prod.data->rows; ++i) {
        for (size_t j = 0; j < prod.data->cols; ++j) {
            double elem = 0;
            for (size_t k = 0; k < data->cols; ++k) {
                elem += data->arr[i][k] * m(k, j);
            }
            prod(i, j) = elem;
        }
    }
    return prod;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
    *this = *this * m;
    return *this;
}

bool Matrix::operator==(const Matrix& m) const
{
	if (data == m.data) {
		return true;
	}

	if (data->rows != m.data->rows || data->cols != m.data->cols) {
		return false;
	}

	for (size_t i = 0; i < data->rows; ++i) {
		for (size_t j = 0; j < data->cols; ++j) {
			if (data->arr[i][j] != m.data->arr[i][j]) {
				return false;
			}
		}
	}

	return true;
}

bool Matrix::operator!=(const Matrix& m) const
{
	return !(*this == m);
}

void incrementSize(std::string* text, size_t& size)
{
	size_t nSize = (size + 1) * 2;
	std::string* newText = new std::string[nSize];
	for (size_t i = 0; i < size; ++i) {
		newText[i] = text[i];
	}
	delete[] text;
	text = newText;
	size = nSize;
}

std::string* readText(std::istream& is, size_t& size)
{
	size = 0;
	std::string line = "";
	size_t maxSize = 10;
	std::string* text = new std::string[maxSize];

	while (!is.eof()) {
		getline(is, line);
		if (line == "") {
			break;
		}
		if (size == maxSize) {
			incrementSize(text, maxSize);
		}
		text[size++] = line;
	}

	return text;
}

size_t countTokens(std::string line, const char delim[])
{
	size_t num = 0;

	char* str = (char*)line.c_str();
	char* token = strtok(str, delim);

	while (token != NULL) {
		num++;
		token = strtok(NULL, delim);
	}

	return num;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
	// std::stod throws invalid_argument or out_of_range

	size_t rows = 0;
	std::string* text = readText(is, rows);

	const char delim[] = " \n";
	size_t cols = countTokens(text[0], delim);

	Matrix newM(rows, cols);

	for (size_t i = 0; i < rows; ++i) {
		size_t j = 0;

		std::string line = text[i];
		char* str = (char*)line.c_str();
		char* token = strtok(str, delim);

		while (token != NULL) {
			// Doing things with token
			if (j == cols) {
				delete[] text;
				throw Matrix::InvalidRead();
			}
			double element = 0;
			try {
				element = std::stod(token);
			} catch (std::invalid_argument const&) {
				delete[] text;
				throw Matrix::InvalidRead();
			}
			newM(i, j++) = element;
			token = strtok(NULL, delim);
		}

		if (j != cols) {
			delete[] text;
			throw Matrix::InvalidRead();
		}
	}

	delete[] text;
	m = newM;
	return is;
}