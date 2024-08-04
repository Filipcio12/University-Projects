#pragma once

#include <iostream>

class ComplexNumber {
    public:
        double real;
        double imaginary;

		ComplexNumber(double real, double imaginary);
        double getAmplitude();
        double getPhase();

        ComplexNumber& operator=(const ComplexNumber& cNum);

        ComplexNumber operator+(const ComplexNumber& cNum);
        ComplexNumber operator+(double num);
        ComplexNumber& operator+=(const ComplexNumber& cNum);
        ComplexNumber& operator+=(double num);

        ComplexNumber operator-(const ComplexNumber& cNum);
        ComplexNumber operator-(double num);
        ComplexNumber& operator-=(const ComplexNumber& cNum);
        ComplexNumber& operator-=(double num);

        ComplexNumber operator*(const ComplexNumber& cNum);
        ComplexNumber operator*(double num);
        ComplexNumber& operator*=(const ComplexNumber& cNum);
        ComplexNumber& operator*=(double num);

        ComplexNumber operator/(const ComplexNumber& cNum);
        ComplexNumber operator/(double num);
        ComplexNumber& operator/=(const ComplexNumber& cNum);
        ComplexNumber& operator/=(double num);

        bool operator==(const ComplexNumber& cNum);
        bool operator==(double num);
        bool operator!=(const ComplexNumber& cNum);
        bool operator!=(double num);
        
};

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cNum);
ComplexNumber operator+(double num, const ComplexNumber& cNum);
ComplexNumber operator-(double num, const ComplexNumber& cNum);
ComplexNumber operator*(double num, const ComplexNumber& cNum);
ComplexNumber operator/(double num, const ComplexNumber& cNum);
bool operator==(double num, const ComplexNumber& cNum);
bool operator!=(double num, const ComplexNumber& cNum);
