#include "Matrix.h"
#include "Vector.h"
#include <algorithm>
#include <stdexcept>
#include <malloc.h>

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    paddedCols = (cols + 3) & ~3;
    data = (float*)_mm_malloc(rows * paddedCols * sizeof(float), 16);
    Fill(0.0f);
}

Matrix::~Matrix() {
    if (data) _mm_free(data);
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), paddedCols(other.paddedCols) {
    data = (float*)_mm_malloc(rows * paddedCols * sizeof(float), 16);
    std::copy(other.data, other.data + (rows * paddedCols), data);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        if (data) _mm_free(data);
        rows = other.rows;
        cols = other.cols;
        paddedCols = other.paddedCols;
        data = (float*)_mm_malloc(rows * paddedCols * sizeof(float), 16);
        std::copy(other.data, other.data + (rows * paddedCols), data);
    }
    return *this;
}

float& Matrix::operator()(int r, int c) {
    return data[r * paddedCols + c];
}

float Matrix::operator()(int r, int c) const {
    return data[r * paddedCols + c];
}

void Matrix::Fill(float value) {
    __m128 v = _mm_set1_ps(value);
    for (int i = 0; i < rows * paddedCols; i += 4) {
        _mm_store_ps(&data[i], v);
    }
}

Matrix Matrix::Identity(int size) {
    Matrix res(size, size);
    for (int i = 0; i < size; ++i) res(i, i) = 1.0f;
    return res;
}

void Matrix::Display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << "\n";
    }
}

Vector Matrix::operator*(const Vector& v) const {
    if (cols != v.size()) throw std::invalid_argument("dimensions are diff");
    Vector res(rows);
    for (int i = 0; i < rows; ++i) {
        __m128 sum = _mm_setzero_ps();
        const float* rowPtr = &data[i * paddedCols];
        const float* vecPtr = v.getRawData();
        for (int j = 0; j < paddedCols; j += 4) {
            sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load_ps(&rowPtr[j]), _mm_load_ps(&vecPtr[j])));
        }
        float t[4];
        _mm_storeu_ps(t, sum);
        res[i] = t[0] + t[1] + t[2] + t[3];
    }
    return res;
}
