#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <xmmintrin.h>
#include "Vector.h"

class Quaternion;

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
    static Matrix Translate(Vector v);
    static Matrix Scale(Vector v);
    static Matrix Rotate(Vector axis, float angle);
    static Matrix transpose(Matrix m);

    void Fill(float value);
    void Display() const;

    Vector operator*(const Vector& v) const;
    Matrix operator*(Matrix m2);

    float* getRawData() const { return data; }
    int GetRows() const { return rows; }
    int GetCols() const { return cols; }
    int GetPaddedCols() const { return paddedCols; }
};

#endif
