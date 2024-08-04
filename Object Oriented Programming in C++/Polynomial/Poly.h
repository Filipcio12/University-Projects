#pragma once
#include <map>
#include <iostream>

class Poly {
    std::map <unsigned int, double> terms;

    public:
        Poly();
        Poly(const Poly& p);
        Poly(double p);
        double& operator[](unsigned int index);
        friend std::ostream& operator<<(std::ostream& os, const Poly& p);
        Poly& operator=(const Poly& p);

        Poly operator+(const Poly& p) const;
        friend Poly operator+(double p1, const Poly& p2);
        
        Poly operator-(const Poly& p) const;
        friend Poly operator-(double p1, const Poly& p2);
        Poly operator-() const; //negation

        Poly operator*(const Poly& p) const;
        friend Poly operator*(double p1, const Poly& p2);
        
        double operator()(double x) const;
};