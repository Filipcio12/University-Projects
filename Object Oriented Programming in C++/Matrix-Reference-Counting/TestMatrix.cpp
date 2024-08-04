#include "Matrix.h"

#include <iostream>
#include <fstream>

// Functionality
void testProcessArray();
void testDefaultConstructor();
void testConstructor();
void testCopyConstructor();
void testAssignment();
void testInputFile();
void testAddition();
void testSubtraction();
void testMultiplication();
void testComparison();

// Exceptions
void testInvalidRange();
void testInvalidSum();
void testInvalidProduct();
void testInvalidRead();

// Reference counting
void testReferenceCounting();

int main()
{
	// Functionality
	testProcessArray();
	testDefaultConstructor();
	testConstructor();
	testCopyConstructor();
	testAssignment();
	testInputFile();
	testAddition();
	testSubtraction();
	testMultiplication();
	testComparison();

	// Exceptions
	testInvalidRange();
	testInvalidSum();
	testInvalidProduct();
	testInvalidRead();

	// Reference Counting
	testReferenceCounting();

	return 0;
}

void testReferenceCounting()
{
	std::cout << "Reference Counting" << std::endl;
	Matrix a(3, 3);
	Matrix b = a;
	std::cout << b(0, 0) << std::endl;

	// Change
	//b(0, 0) = 1;
	//std::cout << b(0, 0) << "\n\n";
}

void testInvalidRead()
{
	std::cout << "InvalidRead:" << std::endl;
	std::fstream invalidRead;
	invalidRead.open("invalidRead.txt", std::ios::in);
	Matrix a;
	try {
		invalidRead >> a;
		std::cout << "not caught" << "\n\n";
	} catch (Matrix::InvalidRead) {
		std::cout << "caught" << "\n\n";
	}
	invalidRead.close();
}

void testInvalidProduct()
{
	std::cout << "InvalidProduct:" << std::endl;
	Matrix a(3, 3);
	Matrix b(4, 3);
	try {
		a * b;
		std::cout << "not caught" << "\n\n";
	} catch (Matrix::InvalidProduct) {
		std::cout << "caught" << "\n\n";
	}
}

void testInvalidSum()
{
	std::cout << "InvalidSum:" << std::endl;
	Matrix a(3, 4);
	Matrix b(4, 3);
	try {
		a + b;
		std::cout << "not caught" << "\n\n";
	} catch (Matrix::InvalidSum) {
		std::cout << "caught" << "\n\n";
	}
}

void testInvalidRange()
{
	std::cout << "InvalidRange:" << std::endl;
	Matrix a(2, 2);
	try {
		a(2, 2);
		std::cout << "not caught" << "\n\n";
	} catch(Matrix::InvalidRange) {
		std::cout << "caught" << "\n\n";
	}
}

void testProcessArray()
{
	std::cout << "Function processArray():" << std::endl;
	double arr[2][2] = {
		{1.2, 2.7},
		{-2, 1.3}
	};
	Matrix a = processArray(arr);
	std::cout << a << std::endl;
}

void testDefaultConstructor()
{
	std::cout << "Default constructor:" << std::endl;
	Matrix a;
	std::cout << a << std::endl;
}

void testConstructor()
{
	std::cout << "Size constructor:" << std::endl;
	Matrix a(2, 2);
	std::cout << a << std::endl;
}

void testCopyConstructor()
{
	std::cout << "Copy constructor:" << std::endl;
	Matrix a(2, 2);
	Matrix b(a);
	std::cout << b << std::endl;
}

void testAssignment()
{
	std::cout << "Assignment:" << std::endl;
	Matrix a(2, 2);
	Matrix b(3, 1);
	b = a;
	std::cout << b << std::endl;
}

void testInputFile()
{
	std::cout << "Input file:" << std::endl;
	std::fstream testFile;
	testFile.open("testFile.txt", std::ios::in);
	Matrix a;
	testFile >> a;
	testFile.close();
	std::cout << a << std::endl;
}

void testAddition()
{
	std::cout << "Addition:" << std::endl;
	double a[2][2] = {
		{1, 2},
		{2, 1}
	};
	double b[2][2] = {
		{1, 0},
		{0, 1}
	};
	Matrix matA = processArray(a);
	Matrix matB = processArray(b);
	std::cout << matA + matB << std::endl;

	std::cout << "Addition assignment:" << std::endl;
	matA += matB;
	std::cout << matA << std::endl;
}

void testSubtraction()
{
	std::cout << "Subtraction:" << std::endl;
	double a[2][2] = {
		{1, 2},
		{2, 1}
	};
	double b[2][2] = {
		{1, 0},
		{0, 1}
	};
	Matrix matA = processArray(a);
	Matrix matB = processArray(b);
	std::cout << matA - matB << std::endl;

	std::cout << "Subtraction assignment:" << std::endl;
	matA -= matB;
	std::cout << matA << std::endl;
}

void testMultiplication()
{
	std::cout << "Multiplication:" << std::endl;
	double a[2][3] = {
		{1, 2, 3},
		{4, 5, 6}
	};
	double b[3][4] = {
		{12, 11, 10, 9},
		{8, 7, 6, 5},
		{4, 3, 2, 1},
	};
	Matrix matA = processArray(a);
	Matrix matB = processArray(b);
	std::cout << matA * matB << std::endl;

	std::cout << "Multiplication assignment:" << std::endl;
	matA *= matB;
	std::cout << matA << std::endl;
}

void testComparison()
{
	std::cout << "Comparison:" << std::endl;
	double a[2][3] = {
		{1, 2, 3},
		{4, 5, 6}
	};
	double b[2][3] = {
		{1, 2, 3},
		{4, 5, 6}
	};
	Matrix matA = processArray(a);
	Matrix matB = processArray(b);
	std::cout << "(a == b) = " << (matA == matB) << std::endl;
	std::cout << "(a != b) = " << (matA != matB) << "\n\n";
}