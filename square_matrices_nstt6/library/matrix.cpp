#include "matrix.h"
#include <cstring>

SqMatrix::SqMatrix(usize size, std::vector<float> diagonal) : size_(size) {
    if (diagonal.size() != size)
        throw std::invalid_argument("Sizes are not same!");
    
    mat_ = new float[size * size];
    for (usize i = 0; i < size; i++)
        mat_[i * (size + 1)] = diagonal[i];
}

SqMatrix::SqMatrix(usize size) : SqMatrix(size, std::vector<float>(size, 1.0f)) {}

SqMatrix::SqMatrix(const SqMatrix& matrix) : size_(matrix.size_){
    mat_ = new float[size_ * size_];

    std::memcpy(mat_, matrix.mat_, sizeof(float) * size_ * size_);
}

SqMatrix::SqMatrix(SqMatrix&& matrix) {
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
