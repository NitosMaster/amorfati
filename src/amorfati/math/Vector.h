#ifndef VECTOR_H
#define VECTOR_H

#include <xmmintrin.h>

class Vector {
private:
    float* data;
    int dimensions;
    int paddedSize;

public:
    Vector(int size);
    Vector(const Vector& other);
    ~Vector();
    Vector& operator=(const Vector& other);

    int size() const { return dimensions; }
    float& operator[](int i) { return data[i]; }
    const float& operator[](int i) const { return data[i]; }
    float* getRawData() const { return data; }

    Vector operator+(const Vector& other) const;
    Vector operator*(float scalar) const;
    float dot(const Vector& other) const;
    float sqr_magnitude() const;
    Vector normalize() const;
    Vector cross(const Vector& other) const;
};

#endif
