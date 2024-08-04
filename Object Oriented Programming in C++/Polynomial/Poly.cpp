#include "Poly.h"
#include <cmath>

Poly::Poly()
{
    terms.clear();
}

Poly::Poly(double p)
{
    terms[0] = p;
}

Poly::Poly(const Poly& p)
{
    for (auto term : p.terms) {
        terms[term.first] = term.second;
    }
}

double& Poly::operator[](unsigned int index)
{
    return terms[index];
}

std::ostream& operator<<(std::ostream& os, const Poly& p)
{
    bool isFirst = true;
    for (auto term = p.terms.rbegin(); term != p.terms.rend(); term++) {
        unsigned int order = term->first;
        double coefficient = term->second;
        char sign = 43 + 2*(coefficient < 0);
        if (coefficient == 0 && order > 0) {
            continue;
        }
        (isFirst && coefficient < 0) ? os << sign : os << "";
        (!isFirst) ? os << " " << sign << " " : os << "";
        (fabs(coefficient) != 1 || order == 0) ? os << fabs(coefficient) : os << "";
        (order > 0) ? os << "x" : os << "";
        (order > 1) ? os << "^" << order : os << "";
        isFirst = false;
    }
    return os;
}

Poly& Poly::operator=(const Poly& p)
{
    terms.clear();
    for (auto term : p.terms) {
        terms[term.first] = term.second;
    }
    return *this;
}

Poly Poly::operator+(const Poly& p) const
{
    Poly sum;
    auto t1 = terms.rbegin();
    auto t2 = p.terms.rbegin();
    while (t1 != terms.rend() && t2 != p.terms.rend()) {
        unsigned int o1 = t1->first, o2 = t2->first;
        double c1 = t1->second, c2 = t2->second;
        if (o1 == o2) {
            sum[o1] = c1 + c2;
            t1++;
            t2++;
        }
        else if (o1 > o2) {
            sum[o1] = c1;
            t1++;
        }
        else {
            sum[o2] = c2;
            t2++;
        }
    }
    return sum;
}

Poly operator+(double p1, const Poly& p2)
{
    return p2 + p1;
}

Poly Poly::operator-(const Poly& p) const
{
    Poly diff;
    auto t1 = terms.rbegin();
    auto t2 = p.terms.rbegin();
    while (t1 != terms.rend() && t2 != p.terms.rend()) {
        unsigned int o1 = t1->first, o2 = t2->first;
        double c1 = t1->second, c2 = t2->second;
        if (o1 == o2) {
            diff[o1] = c1 - c2;
            t1++;
            t2++;
        }
        else if (o1 > o2) {
            diff[o1] = c1;
            t1++;
        }
        else {
            diff[o2] = -c2;
            t2++;
        }
    }
    return diff;
}

Poly operator-(double p1, const Poly& p2)
{
    return p2 - p1;
}

Poly Poly::operator-() const
{
    return 0.0 - *this;
}

Poly Poly::operator*(const Poly& p) const
{
    Poly product = 0;
    for (auto t1 : terms) {
        Poly m = 0;
        unsigned int o1 = t1.first;
        double c1 = t1.second;
        for (auto t2 : p.terms) {
            unsigned int o2 = t2.first;
            double c2 = t2.second;
            m[o1 + o2] = c1 * c2;
        }
        product = product + m;
    }
    return product;
}

Poly operator*(double p1, const Poly& p2)
{
    return p2 * p1;
}

double Poly::operator()(double x) const
{
    double y = 0;
    for (auto t : terms) {
        unsigned int o = t.first;
        double c = t.second;
        y += c * pow(x, o);
    }
    return y;
}