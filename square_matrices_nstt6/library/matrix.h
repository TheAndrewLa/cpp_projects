#pragma once

#include <cstddef>
#include <vector>
#include <stdexcept>

using usize = std::size_t;
using isize = std::ptrdiff_t;

class SqMatrix {
    SqMatrix() = delete;
    SqMatrix(usize size, std::vector<float> diagonal);
    SqMatrix(usize size) noexcept;

    SqMatrix(const SqMatrix& matrix);
    SqMatrix(SqMatrix&& matrix);

    ~SqMatrix();

    SqMatrix& operator=(const SqMatrix& ref);
    SqMatrix& operator=(SqMatrix&& ref);

    explicit operator double();

    bool operator==(const SqMatrix& other);
    bool operator!=(const SqMatrix& other);

    // No checking in this function. LET THE UB OUT!!!
    float* operator[](usize index);

    SqMatrix& operator+(const SqMatrix& other);
    SqMatrix& operator+=(const SqMatrix& other);

    SqMatrix operator*(const SqMatrix& other);
    SqMatrix& operator*=(const SqMatrix& other);

    SqMatrix operator*(float scalar) noexcept;
    SqMatrix& operator*=(float scalar) noexcept;

    inline usize Size() const noexcept {
        return size_;
    }

    private:
    usize size_;
    float *mat_;
};
