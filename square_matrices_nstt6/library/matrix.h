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
    struct RowConst {
        RowConst() = delete;
        RowConst(const RowConst&) = default;
        RowConst(RowConst&&) = default;

        RowConst(float* mat, usize row_index, usize bounds);
        
        ~RowConst() = default;
        
        float operator[](usize index) const;

        private:
        const float* row_;
        usize boundary_;
    };

    struct Row {
        Row() = delete;
        Row(const Row&) = default;
        Row(Row&&) = default;

        Row(float* mat, usize row_index, usize bounds);

        ~Row() = default;

        float& operator[](usize index);

        private:
        float* row_;
        usize boundary_;
    };

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

    Row operator[](usize index);
    RowConst operator[](usize index) const;

    SqMatrix operator+(const SqMatrix& other) const;
    SqMatrix& operator+=(const SqMatrix& other);

    SqMatrix operator*(const SqMatrix& other) const;
    SqMatrix& operator*=(const SqMatrix& other);

    SqMatrix operator*(float scalar) const noexcept;
    SqMatrix& operator*=(float scalar) noexcept;

    friend SqMatrix operator*(float scalar, const SqMatrix& mat);

    inline usize size() const noexcept {
        return size_;
    }

    std::string to_string() const noexcept;

    private:
    usize size_;
    float *mat_;
};
