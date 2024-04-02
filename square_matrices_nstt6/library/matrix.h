#pragma once
#include <cstddef>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;

class SqMatrix {
    SqMatrix() = delete;
    SqMatrix(usize size);
    SqMatrix(usize size, std::vector<float> diagonal);

    SqMatrix(const SqMatrix& matrix);
    SqMatrix(SqMatrix&& matrix);

    ~SqMatrix();

    SqMatrix& operator=(const SqMatrix& ref);
    SqMatrix& operator=(SqMatrix&& ref);

    explicit operator double();

    bool operator==(const SqMatrix& other);
    bool operator!=(const SqMatrix& other);

    SqMatrix& operator+(const SqMatrix& other);
    SqMatrix& operator+=(const SqMatrix& other);

    SqMatrix operator*(const SqMatrix& other);
    SqMatrix& operator*=(const SqMatrix& other);

    SqMatrix operator*(float scalar);
    SqMatrix& operator*=(float scalar);

    private:
    usize size_;
    float *mat_;
};
