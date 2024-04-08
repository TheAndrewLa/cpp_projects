#include "matrix.h"
#include <cstring>

SqMatrix::RowConst::RowConst(float* mat, usize row_index, usize bounds) {
    boundary_ = bounds;
    row_ = const_cast<const float*>(mat + (row_index * bounds));
}

float SqMatrix::RowConst::operator[](usize index) const {
    assert(row_ != nullptr);
    assert(boundary_ > 0);

    if (index >= boundary_)
        throw std::out_of_range("Column index out of range!");

    return row_[index];
}

SqMatrix::Row::Row(float* mat, usize row_index, usize bounds) {
    boundary_ = bounds;
    row_ = mat + (row_index * bounds);
}

float& SqMatrix::Row::operator[](usize index) {
    assert(row_ != nullptr);
    assert(boundary_ > 0);

    if (index >= boundary_)
        throw std::out_of_range("Column index out of range!");

    return row_[index];
}

SqMatrix::SqMatrix() noexcept : SqMatrix(4) {}

SqMatrix::SqMatrix(usize size) noexcept {
    size_ = size;
    mat_ = new float[size * size]();
}

SqMatrix::SqMatrix(std::vector<float> diagonal) noexcept : SqMatrix(diagonal.size()) {
    for (usize i = 0; i < size_; i++)
        mat_[i * (size_ + 1)] = diagonal[i];
}

SqMatrix::SqMatrix(const SqMatrix& matrix) {
    if (matrix.mat_ == nullptr || matrix.size_ == 0)
        throw std::invalid_argument("Invalid matrix was given!");

    size_ = matrix.size_;
    mat_ = new float[size_ * size_];
    std::memcpy(mat_, matrix.mat_, sizeof(float) * size_ * size_);
}

SqMatrix::SqMatrix(SqMatrix&& matrix) {
    if (mat_ == nullptr || size_ == 0)
        throw std::invalid_argument("Invalid matrix was given!");

    size_ = matrix.size_;
    mat_ = matrix.mat_;

    matrix.mat_ = nullptr;
}

SqMatrix::~SqMatrix() {
    delete[] mat_;
}

SqMatrix& SqMatrix::operator=(const SqMatrix& ref) {
    delete[] mat_;

    size_ = ref.size_;
    mat_ = new float[size_ * size_];

    std::memcpy(mat_, ref.mat_, sizeof(float) * size_ * size_);

    return *this;
}

SqMatrix& SqMatrix::operator=(SqMatrix&& ref) {
    delete[] mat_;

    size_ = ref.size_;
    mat_ = ref.mat_;

    ref.mat_ = nullptr;

    return *this;
}

SqMatrix::operator float() {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    float res = 0;
    for (usize i = 0; i < size_; i++)
        for (usize j = 0; j < size_; j++)
            res += mat_[j + (i * size_)];

    return res;
}

bool SqMatrix::operator!=(const SqMatrix& other) const {
    if (size_ != other.size_)
        return true;

    return std::memcmp(mat_, other.mat_, size_ * size_ * sizeof(float)) != 0;
}

bool SqMatrix::operator==(const SqMatrix& other) const {
    if (size_ != other.size_)
        return false;

    return std::memcmp(mat_, other.mat_, size_ * size_ * sizeof(float)) == 0;
}

SqMatrix::Row SqMatrix::operator[](usize index) {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    if (index >= size_)
        throw std::out_of_range("Row index out of range!");

    return SqMatrix::Row{mat_, index, size_};
}

SqMatrix::RowConst SqMatrix::operator[](usize index) const {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    if (index >= size_)
        throw std::out_of_range("Row index out of range!");

    return SqMatrix::RowConst{mat_, index, size_};
}

SqMatrix SqMatrix::operator+(const SqMatrix& other) const {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    assert(other.mat_ != nullptr);
    assert(other.size_ > 0);

    if (size_ != other.size_)
        throw std::invalid_argument("Size of matrices should be the same!");

    SqMatrix res{*this};
    res += other;

    return res;
}

SqMatrix& SqMatrix::operator+=(const SqMatrix& other) {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    assert(other.mat_ != nullptr);
    assert(other.size_ > 0);

    if (size_ != other.size_)
        throw std::invalid_argument("Size of matrices should be the same!");

    for (usize i = 0; i < size_; i++) {
        for (usize j = 0; j < size_; j++) {
            mat_[j + (i * size_)] += other.mat_[j + (i * size_)];
        }
    }

    return *this;
}

SqMatrix SqMatrix::operator*(const SqMatrix& other) const {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    assert(other.mat_ != nullptr);
    assert(other.size_ > 0);

    if (size_ != other.size_)
        throw std::invalid_argument("Size of matrices should be the same!");

    SqMatrix result{size_};

    for (usize i = 0; i < size_; i++) {
        for (usize j = 0; j < size_; j++) {
            for (usize k = 0; k < size_; k++) {
                result[i][j] += (*this)[i][k] * other[k][j];
            }
        }
    }

    return result;
}

SqMatrix& SqMatrix::operator*=(const SqMatrix& other) {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    assert(other.mat_ != nullptr);
    assert(other.size_ > 0);

    *this = (*this) * other;
    return *this;
}

SqMatrix SqMatrix::operator*(float scalar) const noexcept {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    SqMatrix result{*this};

    for (usize i = 0; i < size_; i++)
        for (usize j = 0; j < size_; j++)
            result.mat_[j + (i * size_)] *= scalar;

    return result;
}

SqMatrix& SqMatrix::operator*=(float scalar) noexcept {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    for (usize i = 0; i < size_; i++)
        for (usize j = 0; j < size_; j++)
            mat_[j + (i * size_)] *= scalar;

    return *this;
}

SqMatrix operator*(float scalar, const SqMatrix& mat) {
    assert(mat.mat_ != nullptr);
    assert(mat.size_ > 0);

    return mat * scalar;
}

std::string SqMatrix::to_string() const noexcept {
    assert(mat_ != nullptr);
    assert(size_ > 0);

    std::ostringstream oss;

    for (usize i = 0; i < size_; i++) {
        for (usize j = 0; j < size_; j++)
            oss << mat_[j + (i * size_)] << ' ';

        oss << '\n';
    }

    return oss.str();
}
