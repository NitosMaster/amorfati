#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <xmmintrin.h>

class Vector;

class Matrix {
private:
    int rows, cols;
    int paddedCols;
    float* data;

public:
    Matrix(int r, int c);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    float& operator()(int r, int c);
    float operator()(int r, int c) const;

    static Matrix Identity(int size);
    void Fill(float value);
    void Display() const;

    Vector operator*(const Vector& v) const;

    float* getRawData() const { return data; }
    int GetRows() const { return rows; }
    int GetCols() const { return cols; }
};

#endif
