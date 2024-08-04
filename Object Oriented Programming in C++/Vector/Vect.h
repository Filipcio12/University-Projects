#pragma once

class Vect {
    double* data;
    unsigned int size;
    unsigned int maxSize;
    
    public:
        class Range {};
        Vect();
        Vect(const Vect& v);
        Vect(unsigned int nSize);
        ~Vect();

        void setElement(unsigned int index, double val);
        void print();
        unsigned int getSize();
        double getAverage();
        double getMin();

        Vect concatenate(const Vect& v);
};