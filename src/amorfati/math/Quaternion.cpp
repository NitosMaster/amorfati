#include<iostream>
#include<xmmintrin.h>
#include<malloc.h>
#include "Quaternion.h"
#include "Matrix.h"

Quaternion::Quaternion(float w, float x, float y, float z) {
    data = (float*)_mm_malloc(4 * sizeof(float), 16);
    data[0] = w;
    data[1] = x;
    data[2] = y;
    data[3] = z;
}

Quaternion::~Quaternion() {
    if (data) _mm_free(data);
}

Quaternion Quaternion::operator*(Quaternion q2) {
    Quaternion product(0, 0, 0, 0);

    product.data[0] = data[0] * q2.data[0] - data[1] * q2.data[1] - data[2] * q2.data[2] - data[3] * q2.data[3];
    product.data[1] = data[0] * q2.data[1] + data[1] * q2.data[0] + data[2] * q2.data[3] - data[3] * q2.data[2];
    product.data[2] = data[0] * q2.data[2] - data[1] * q2.data[3] + data[2] * q2.data[0] + data[3] * q2.data[1];
    product.data[3] = data[0] * q2.data[3] + data[1] * q2.data[2] - data[2] * q2.data[1] + data[3] * q2.data[0];

    return product;
}

float Quaternion::sqrMagnitude() const {
    float quaMag = data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3];
    return quaMag;
}

Quaternion Quaternion::normalize() const {
    float quaMag = sqrMagnitude();
    if (quaMag == 0.0f) return *this;
    float invQua;
    __m128 in = _mm_set_ss(quaMag);
    __m128 res = _mm_rsqrt_ss(in);
    __m128 mccs = _mm_mul_ss(_mm_set_ss(0.5f), _mm_mul_ss(in, _mm_mul_ss(res, res)));
    res = _mm_mul_ss(res, _mm_sub_ss(_mm_set_ss(1.5f), mccs));
    _mm_store_ss(&invQua, res);
    return (*this) * invQua;
}

Quaternion Quaternion::operator*(float scalar) const {
    Quaternion newQ(0, 0, 0, 0);
    __m128 s = _mm_set1_ps(scalar);
    _mm_store_ps(&newQ.data[0], _mm_mul_ps(_mm_load_ps(&data[0]), s));
    
    return newQ;
}

Matrix Quaternion::toRotationMatrix() const {
    Matrix m(4, 4);

    /*«== i hate this fuckin expansion, like why is it so long,
    to see the code on my laptop I needed to not add spaces between *
    WHYYYYY?!?!?!??!?!??!???!!?!??! ==»*/

    m(0, 0) = 1 - 2*(data[2]*data[2] + data[3]*data[3]);
    m(0, 1) = 2*(data[1]*data[2] - data[0]*data[3]);
    m(0, 2) = 2*(data[1]*data[3] + data[0]*data[2]);
    m(1, 0) = 2*(data[1]*data[2] + data[0]*data[3]);
    m(1, 1) = 1 - 2*(data[1]*data[1] + data[3]*data[3]);
    m(1, 2) = 2*(data[2]*data[3] - data[0]*data[1]);
    m(2, 0) = 2*(data[1]*data[3] - data[0]*data[2]);
    m(2, 1) = 2*(data[2]*data[3] + data[0]*data[1]);
    m(2, 2) = 1 - 2*(data[1]*data[1] + data[2]*data[2]);
    m(3, 3) = 1.0f;

    return m;
}
