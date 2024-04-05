#pragma once

#include <cstddef>
#include <cassert>

#include <vector>

#include <string>
#include <sstream>

#include <stdexcept>

using usize = std::size_t;
using isize = std::ptrdiff_t;

class SqMatrix {
    public:
    SqMatrix() noexcept;
    SqMatrix(usize size) noexcept;
    SqMatrix(std::vector<float> diagonal) noexcept;

    SqMatrix(const SqMatrix& matrix);
    SqMatrix(SqMatrix&& matrix);

    ~SqMatrix();

    SqMatrix& operator=(const SqMatrix& ref);
    SqMatrix& operator=(SqMatrix&& ref);

    explicit operator float();

    bool operator==(const SqMatrix& other) const;
    bool operator!=(const SqMatrix& other) const;

    // No index checking in this function
    // LET THE UB OUT!!!

    inline float* operator[](usize index) {
        assert(mat_ != nullptr);
        assert(size_ > 0);

        return reinterpret_cast<float*>(mat_ + (index * size_));
    }

    inline const float* operator[](usize index) const {
        assert(mat_ != nullptr);
        assert(size_ > 0);

        return reinterpret_cast<const float*>(mat_ + (index * size_));
    }

    SqMatrix operator+(const SqMatrix& other) const;
    SqMatrix& operator+=(const SqMatrix& other);

    // AND NOW.....
    // STRASSEN APPEARS (actually, no)

    SqMatrix operator*(const SqMatrix& other) const;
    SqMatrix& operator*=(const SqMatrix& other);

    SqMatrix operator*(float scalar) const noexcept;
    SqMatrix& operator*=(float scalar) noexcept;

    inline usize size() const noexcept {
        return size_;
    }

    std::string to_string() const noexcept;

    private:
    usize size_;
    float *mat_;
};
