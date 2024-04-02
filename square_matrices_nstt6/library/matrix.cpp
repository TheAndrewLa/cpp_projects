#include "matrix.h"
#include <cstring>

SqMatrix::SqMatrix(usize size) noexcept : size_(size) {
    mat_ = new float[size_ * size_];
    for (usize i = 0; i < size_; i++)
        for (usize j = 0; j < size_; j++)
            mat_[i * size_ + j] = 0;

    for (usize i = 0; i < size_; i++)
        mat_[i * (size + 1)] = 1;
}

SqMatrix::SqMatrix(std::vector<float> diagonal) : SqMatrix(diagonal.size()) {
    for (usize i = 0; i < size_; i++)
        mat_[i * (size_ + 1)] = diagonal[i];
}

SqMatrix::SqMatrix(const SqMatrix& matrix) : size_(matrix.size_) {
    mat_ = new float[size_ * size_];
    std::memcpy(mat_, matrix.mat_, sizeof(float) * size_ * size_);
}

SqMatrix::SqMatrix(SqMatrix&& matrix) : size_(matrix.size_), mat_(matrix.mat_) {
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

bool SqMatrix::operator!=(const SqMatrix& other) const {
    if (size_ != other.size_)
        return true;
    
    return std::memcmp(mat_, other.mat_, size_ * size_ * sizeof(float)) != 0;
}

bool SqMatrix::operator==(const SqMatrix& other) const {
    if (size_ != other.size_)
        return false;
    
    return std::memcmp(mat_, other.mat_, size_ * size_ * sizeof(float)) == 0;
    // return !(*this != other);
}

float* SqMatrix::operator[](usize index) {
    return reinterpret_cast<float*>(mat_ + (index * size_));
}

SqMatrix::operator float() {
    float res = 0;
    for (usize i = 0; i < size_; i++)
        for (usize j = 0; j < size_; j++)
            res += mat_[i * size_ + j];

    return res;
}
