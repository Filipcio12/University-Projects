#include "Polygon.h"

struct Polygon::rcPolygon {
    Point* vertices;
    unsigned int size, capacity, rc;

    rcPolygon() 
    {
        rc = 1;
        size = 0;
        capacity = 0;
        vertices = NULL;
    }
    ~rcPolygon() 
    {
        delete[] vertices;
    }
    rcPolygon* detach()
    {
        if (rc == 1) {
            return this;
        }
        rcPolygon* poly = new rcPolygon();
        
        poly->size = size;
        poly->capacity = size;

        vertices = new Point[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            poly->vertices[i] = vertices[i];
        }
        rc--;
        return poly;
    }
    private:
        rcPolygon(const rcPolygon&) = delete;
        rcPolygon& operator=(const rcPolygon&) = delete;
};

Polygon::Polygon() 
{
    data = new rcPolygon();
}

Polygon::Polygon(const Polygon& poly)
{
    data = poly.data;
    data->rc++;
}

Polygon::~Polygon() 
{
    if (--data->rc == 0) {
        delete data;
    }
}

void Polygon::add(Point p) 
{
    data = data->detach();
    if (data->size + 1 > data->capacity) {
        unsigned int newCapacity = (data->capacity + 1) * 2;
        Point* newVertices = new Point[newCapacity];
        for (unsigned int i = 0; i < data->size; ++i) {
            newVertices[i] = data->vertices[i];
        }
        delete[] data->vertices;
        data->vertices = newVertices;
        data->capacity = newCapacity;
    }
    data->vertices[data->size++] = p;
}

std::ostream& operator<<(std::ostream& os, const Polygon& poly) 
{
    for (unsigned int i = 0; i < poly.data->size; ++i) {
        os << "point " << i << ": " << poly.data->vertices[i] << "\n";
    }
    return os;
}

Polygon& Polygon::operator=(const Polygon& poly) 
{
    if (--data->rc == 0) {
        delete data;
    }
    data = poly.data;
    data->rc++;
    return *this;
}

Polygon Polygon::operator+(const Point& v)
{
    Polygon result(*this);
    for (unsigned int i = 0; i < data->size; ++i) {
        result.data->vertices[i] += v;
    }
    return result;
}

Point& Polygon::operator[](unsigned int idx) 
{
    //data = data->detach();
    if (idx + 1 > data->size) {
        throw IndexOutOfBoundsException();
    }
    return data->vertices[idx];
}