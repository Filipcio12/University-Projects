#include "Vect.h"
#include <iostream>

Vect::Vect()
{
    data = NULL;
    size = 0;
    maxSize = 0;
}

Vect::Vect(unsigned int nSize)
{
    data = new double[nSize];
    for (unsigned int i = 0; i < nSize; ++i) {
        data[i] = 0;
    }
    size = nSize;
    maxSize = nSize;
}

Vect::Vect(const Vect& v)
{
    data = new double[v.size];
    for (unsigned int i = 0; i < v.size; ++i) {
        data[i] = v.data[i];
    }
    size = v.size;
    maxSize = v.maxSize;
}

Vect::~Vect()
{
    delete[] data;
}

void Vect::setElement(unsigned int index, double val)
{
    if (index >= size) {
        throw Range();
    }
    data[index] = val;
}

void Vect::print() 
{
    std::cout << "[";
    for (unsigned int i = 0; i < size; ++i) {
        std::cout << data[i];
        if (i != (size - 1)) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

unsigned int Vect::getSize()
{
    return size;
}

double Vect::getAverage()
{
    double avg = 0;
    for (unsigned int i = 0; i < size; ++i) {
        avg += data[i];
    }
    return (avg / size);
}

double Vect::getMin()
{
    if (size == 0) {
        return 0;
    }
    double min = data[0];
    for (unsigned int i = 1; i < size; ++i) {
        min = (min > data[i]) ? data[i] : min;
    }
    return min;
}

Vect Vect::concatenate(const Vect& v)
{
    Vect res(size + v.size);
    for (unsigned int i = 0; i < size; ++i) {
        res.data[i] = data[i];
    }
    for (unsigned int i = 0; i < v.size; ++i) {
        res.data[i + size] = v.data[i];
    }
    return res;
}