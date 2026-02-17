#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"
#include<algorithm>
#include<stdexcept>
#include<malloc.h>
#include<cmath> /*«== we kept the no cmath circus goin for quite
                a while. CPU sin and cos are shit so... ==»*/

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

Matrix& Matrix::operator=(const Matrix& other) { //«== beautiful naming ain't it? ==»//
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
    Matrix rez(size, size);
    for (int i = 0; i < size; ++i) rez(i, i) = 1.0f;
    return rez;
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

Matrix Matrix::Translate(Vector v) {
    Matrix identity = Matrix::Identity(v.size() + 1); //«== See what I did there? ==»//

    for (int i = 0; i < v.size(); i++) {
        identity(i, v.size() + 1) = v[i];
    }

    return identity;
}

/*«== totally unrelated, but to whomever
    might be reading this src, i use i++,
which might feel out of character
    for the guy that's using SIMD instead of
letting the compiler do it's thing.
    I don't like how ++i looks is all. ==»*/

Matrix Matrix::transpose(Matrix m) {
    Matrix transM(m.cols, m.rows); //«== yes i named it like this on purpose ==»//
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            transM(j, i) = m(i, j);
        }
    }

    return transM;
}

Matrix Matrix::operator*(Matrix m2) {
    Matrix transM2 = transpose(m2);
    Matrix product(rows, m2.cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < transM2.rows; j++) {
            __m128 sum = _mm_setzero_ps();
            const float* rowA = &data[i * paddedCols];
            const float* rowB = &transM2.data[j * transM2.paddedCols];
            for (int k = 0; k < paddedCols; k += 4) {
                sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load_ps(&rowA[k]),
                _mm_load_ps(&rowB[k])));
            }
            float t[4];
            _mm_storeu_ps(t, sum);
            product(i, j) = t[0] + t[1] + t[2] + t[3];
        }
    }

    return product;
}

Matrix Matrix::Scale(Vector dihh) {
    Matrix diagonalPenis = Matrix::Identity(dihh.size() + 1);

    for (int i = 0; i < dihh.size(); i++) {
        diagonalPenis(i, i) = dihh[i];
    }

    return diagonalPenis;
}

Matrix Matrix::Rotate(Vector axis, float angle) {
    Quaternion q(cos(angle/2), axis[0]*sin(angle/2), axis[1]*sin(angle/2), axis[2]*sin(angle/2));
    Quaternion nQ = q.normalize();

    return nQ.toRotationMatrix();
}
