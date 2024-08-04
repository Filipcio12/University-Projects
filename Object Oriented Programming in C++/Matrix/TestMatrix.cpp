#include "Matrix.h"
#include <iostream>
#include <fstream>

int main()
{
    Matrix a, b;
    std::fstream data;
    data.open("data.txt", std::ios::in);
    data >> a;
    data >> b;
    data.close();
    std::cout << a << "\n" << b << "\n" << a * b;
    /*Matrix a(2, 3);
    Matrix b(3, 2);

    a(0, 0) = 1;
    a(0, 1) = 2;
    a(0, 2) = 3;
    a(1, 0) = 4;
    a(1, 1) = 5;
    a(1, 2) = 6;

    b(0, 0) = 7;
    b(0, 1) = 8;
    b(1, 0) = 9;
    b(1, 1) = 10;
    b(2, 0) = 11;
    b(2, 1) = 12;

    a *= b;

    std::cout << a;*/ 
    return 0;
}