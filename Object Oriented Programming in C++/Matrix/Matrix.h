#pragma once
#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h> 

class Matrix {
    double** arr;
    size_t m;
    size_t n;

    public:   
        Matrix();
        Matrix(size_t m, size_t n);
        Matrix(const Matrix& matrix);
        ~Matrix();
        double operator()(size_t m, size_t n) const; // read only
        double& operator()(size_t m, size_t n); // write
        size_t getNumOfRows() const;
        size_t getNumOfColumns() const;
        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
        Matrix& operator=(const Matrix& matrix);
        Matrix operator+(const Matrix& matrix) const;
        Matrix& operator+=(const Matrix& matrix);
        Matrix operator-(const Matrix& matrix) const;
        Matrix& operator-=(const Matrix& matrix);
        Matrix operator*(const Matrix& matrix);
        Matrix& operator*=(const Matrix& matrix);
        friend std::istream& operator>>(std::istream& is, Matrix& m);
        friend void readText(std::istream& is, std::string* text, 
                                size_t& numOfRows, size_t& textSize);
        friend size_t countNumOfColumns(std::string line);
        friend std::string* seperateElementsInAString(std::string line, size_t numOfElements);
};

class InvalidMatrixElement : public std::exception {
    public:
        const char* what() {
            return "There is no such element in the matrix.";
        }
};

class InvalidMatrixAddition : public std::exception {
    public:
        const char* what() {
            return "Matrices have to be the same size to add.";
        }
};

class InvalidMatrixSubtraction: public std::exception {
    public:
        const char* what() {
            return "Matrices have to be the same size to subtract.";
        }
};

class InvalidMatrixMultiplication: public std::exception {
    public:
        const char* what() {
            return "Matrices can be multiplied only if "
                    "the number of columns of the first "
                    "is equal to the number of rows of the second.";
        }
};

class InvalidMatrixInput: public std::exception {
    public:
        const char* what() {
            return "Matrix has to have the same number of columns per each row.";
        }
};