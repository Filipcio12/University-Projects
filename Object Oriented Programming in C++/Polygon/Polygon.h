#include <iostream>

struct Point {
    double x;
    double y;

    Point() = default;
    Point(double xx, double yy) : x(xx), y(yy) {};
    Point& operator=(const Point& p) {x = p.x; y = p.y; return *this;}
    Point& operator+=(const Point& v) {x += v.x; y += v.y; return *this;};

    friend std::ostream& operator<<(std::ostream& os, const Point& p) 
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

class Polygon {
    struct rcPolygon;
    rcPolygon* data;

    public:
        Polygon();
        Polygon(const Polygon& poly);
        ~Polygon();
        void add(Point p);
        friend std::ostream& operator<<(std::ostream& os, const Polygon& poly);
        Polygon& operator=(const Polygon& poly);
        Polygon operator+(const Point& v);
        Point& operator[](unsigned int idx);
        class IndexOutOfBoundsException {};
};