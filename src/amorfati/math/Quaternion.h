#ifndef QUATERNION_H
#define QUATERNION_H

#include <xmmintrin.h>
#include <malloc.h>
#include "Matrix.h"

class Quaternion {
private:
    float* data;

public:
    Quaternion(float w, float x, float y, float z);
    ~Quaternion();

    Quaternion operator*(Quaternion q2);
    Quaternion operator*(float scalar) const;

    float sqrMagnitude() const;
    Quaternion normalize() const;
    Matrix toRotationMatrix() const;
};

#endif
