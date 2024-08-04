#include "Complex.h"
#include <cmath>

ComplexNumber::ComplexNumber(double real, double imaginary)
{
    this->real = real;
    this->imaginary = imaginary;
}

double ComplexNumber::getAmplitude()
{
    return (sqrt(real*real + imaginary*imaginary));
}

double ComplexNumber::getPhase()
{
    return (atan(imaginary / real));
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber& cNum)
{
    real = cNum.real;
    imaginary = cNum.imaginary;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cNum)
{
    char sign = 43 + 2*(cNum.imaginary < 0);
    os << cNum.real << " " << sign << " i" << fabs(cNum.imaginary);
    return os;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& cNum)
{
    ComplexNumber sum(real + cNum.real, imaginary + cNum.imaginary);
    return sum;
}

ComplexNumber ComplexNumber::operator+(double num)
{
    ComplexNumber sum(real + num, imaginary);
    return sum;
}

ComplexNumber operator+(double num, const ComplexNumber& cNum)
{
    ComplexNumber sum(cNum.real + num, cNum.imaginary);
    return sum;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& cNum)
{
    *this = *this + cNum;
    return *this;
}

ComplexNumber& ComplexNumber::operator+=(double num)
{
    *this = *this + num;
    return *this;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& cNum)
{
    ComplexNumber diff(real - cNum.real, imaginary - cNum.imaginary);
    return diff;
}

ComplexNumber ComplexNumber::operator-(double num)
{
    ComplexNumber diff(real - num, imaginary);
    return diff;
}

ComplexNumber operator-(double num, const ComplexNumber& cNum)
{
    ComplexNumber diff(num - cNum.real, 0 - cNum.imaginary);
    return diff;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& cNum)
{
    *this = *this - cNum;
    return *this;
}

ComplexNumber& ComplexNumber::operator-=(double num)
{
    *this = *this - num;
    return *this;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& cNum)
{
    ComplexNumber product(real*cNum.real - imaginary*cNum.imaginary, 
                    real*cNum.imaginary + imaginary*cNum.real);
    return product;
}

ComplexNumber ComplexNumber::operator*(double num)
{
    ComplexNumber product(real*num, imaginary*num);
    return product;
}

ComplexNumber operator*(double num, const ComplexNumber& cNum)
{
    ComplexNumber product(cNum.real*num, cNum.imaginary*num);
    return product;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& cNum)
{
    *this = *this * cNum;
    return *this;
}

ComplexNumber& ComplexNumber::operator*=(double num)
{
    *this = *this * num;
    return *this;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber& cNum)
{
    double denominator = (cNum.real*cNum.real + cNum.imaginary*cNum.imaginary);
    if (!denominator) {
        fprintf(stderr, "Can't divide by zero.\n");
        abort();
    }
    ComplexNumber quotient((real*cNum.real + imaginary*cNum.imaginary) / denominator,
                            (imaginary*cNum.real - real*cNum.imaginary) / denominator);
    return quotient;
}

ComplexNumber ComplexNumber::operator/(double num)
{
    if (!num) {
        fprintf(stderr, "Can't divide by zero.\n");
        abort();
    }
    ComplexNumber quotient(real/num, imaginary/num);
    return quotient;
}

ComplexNumber operator/(double num, const ComplexNumber& cNum)
{
    double denominator = (cNum.real*cNum.real + cNum.imaginary*cNum.imaginary);
    if (!denominator) {
        fprintf(stderr, "Can't divide by zero.\n");
        abort();
    }
    ComplexNumber quotient(num*cNum.real/denominator, 
                            -num*cNum.imaginary/denominator);
    return quotient;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& cNum)
{
    *this = *this / cNum;
    return *this;
}

ComplexNumber& ComplexNumber::operator/=(double num)
{
    *this = *this / num;
    return *this;
}

bool ComplexNumber::operator==(const ComplexNumber& cNum)
{
    return (real == cNum.real && imaginary == cNum.imaginary);
}

bool ComplexNumber::operator==(double num)
{
    return (real == num && imaginary == 0);
}

bool operator==(double num, const ComplexNumber& cNum)
{
    return (cNum.real == num && cNum.imaginary == 0);
}

bool ComplexNumber::operator!=(const ComplexNumber& cNum)
{
    return !(real == cNum.real && imaginary == cNum.imaginary);
}

bool ComplexNumber::operator!=(double num)
{
    return !(real == num && imaginary == 0);
}

bool operator!=(double num, const ComplexNumber& cNum)
{
    return !(cNum.real == num && cNum.imaginary == 0);
}
