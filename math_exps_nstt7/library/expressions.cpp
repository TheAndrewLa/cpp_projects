#include "expressions.h"

BinaryOperation::BinaryOperation(Expression* left, Expression* right) {
    if (left == nullptr || right == nullptr)
        throw std::invalid_argument("Both expressions has to be valid!");
    
    left_ = left;
    right_ = right;
}

BinaryOperation::~BinaryOperation() {
    delete left_;
    delete right_;
}

UnaryOperation::UnaryOperation(Expression* main) {
    if (main == nullptr)
        throw std::invalid_argument("Expression has to be valid!");
    
    main_ = main;
}

UnaryOperation::~UnaryOperation() {
    delete main_;
}
