#include "Vector.h"
#include <malloc.h>
#include <algorithm>

Vector::Vector(int size) : dimensions(size) {
    paddedSize = (dimensions + 3) & ~3;
    data = (float*)_mm_malloc(paddedSize * sizeof(float), 16);
    for (int i = 0; i < paddedSize; ++i) data[i] = 0.0f;
}

Vector::Vector(const Vector& other) : dimensions(other.dimensions), paddedSize(other.paddedSize) {
    data = (float*)_mm_malloc(paddedSize * sizeof(float), 16);
    std::copy(other.data, other.data + paddedSize, data);
}

Vector::~Vector() {
    if (data) _mm_free(data);
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        if (data) _mm_free(data);
        dimensions = other.dimensions;
        paddedSize = other.paddedSize;
        data = (float*)_mm_malloc(paddedSize * sizeof(float), 16);
        std::copy(other.data, other.data + paddedSize, data);
    }
    return *this;
}

float Vector::dot(const Vector& other) const {
    __m128 sum = _mm_setzero_ps();
    for (int i = 0; i < paddedSize; i += 4) {
        sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load_ps(&data[i]), _mm_load_ps(&other.data[i])));
    }
    float t[4];
    _mm_storeu_ps(t, sum);
    return t[0] + t[1] + t[2] + t[3];
}

float Vector::sqr_magnitude() const {
    return this->dot(*this);
}

Vector Vector::normalize() const {
    float sqrMag = sqr_magnitude();
    if (sqrMag == 0.0f) return *this;
    float invSqrt;
    __m128 in = _mm_set_ss(sqrMag);
    __m128 res = _mm_rsqrt_ss(in);
    __m128 mccs = _mm_mul_ss(_mm_set_ss(0.5f), _mm_mul_ss(in, _mm_mul_ss(res, res)));
    res = _mm_mul_ss(res, _mm_sub_ss(_mm_set_ss(1.5f), mccs));
    _mm_store_ss(&invSqrt, res);
    return (*this) * invSqrt;
}

Vector Vector::cross(const Vector& other) const {
    if (dimensions == 3 && other.dimensions == 3) {
        Vector res(3);
        res[0] = (data[1] * other.data[2]) - (data[2] * other.data[1]);
        res[1] = (data[2] * other.data[0]) - (data[0] * other.data[2]);
        res[2] = (data[0] * other.data[1]) - (data[1] * other.data[0]);
        return res;
    } else if (dimensions == 7 && other.dimensions == 7) {
        Vector res(7);
        const float* a = data;
        const float* b = other.data;
        res[0] = a[1]*b[3] - a[3]*b[1] + a[2]*b[6] - a[6]*b[2] + a[4]*b[5] - a[5]*b[4];
        res[1] = a[2]*b[4] - a[4]*b[2] + a[3]*b[0] - a[0]*b[3] + a[5]*b[6] - a[6]*b[5];
        res[2] = a[3]*b[5] - a[5]*b[3] + a[4]*b[1] - a[1]*b[4] + a[6]*b[0] - a[0]*b[6];
        res[3] = a[4]*b[6] - a[6]*b[4] + a[5]*b[2] - a[2]*b[5] + a[0]*b[1] - a[1]*b[0];
        res[4] = a[5]*b[0] - a[0]*b[5] + a[6]*b[3] - a[3]*b[6] + a[1]*b[2] - a[2]*b[1];
        res[5] = a[6]*b[1] - a[1]*b[6] + a[0]*b[4] - a[4]*b[0] + a[2]*b[3] - a[3]*b[2];
        res[6] = a[0]*b[2] - a[2]*b[0] + a[1]*b[5] - a[5]*b[1] + a[3]*b[4] - a[4]*b[3];
        return res;
    }
    return Vector(dimensions);
}

Vector Vector::operator+(const Vector& other) const {
    Vector res(dimensions);
    for (int i = 0; i < paddedSize; i += 4) {
        _mm_store_ps(&res.data[i], _mm_add_ps(_mm_load_ps(&data[i]), _mm_load_ps(&other.data[i])));
    }
    return res;
}

Vector Vector::operator-(const Vector& other) const {
    Vector res(dimensions);
    for (int i = 0; i < paddedSize; i += 4) {
        _mm_store_ps(&res.data[i], _mm_sub_ps(_mm_load_ps(&data[i]), _mm_load_ps(&other.data[i])));
    }
    return res;
}

Vector Vector::operator*(float scalar) const {
    Vector res(dimensions);
    __m128 s = _mm_set1_ps(scalar);
    for (int i = 0; i < paddedSize; i += 4) {
        _mm_store_ps(&res.data[i], _mm_mul_ps(_mm_load_ps(&data[i]), s));
    }
    return res;
}
