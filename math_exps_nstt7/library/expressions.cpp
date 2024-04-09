#include "expressions.hpp"

/// @todo FILL THIS CODE WITH ASSERTS

BinaryOperation::BinaryOperation(Expression* left, Expression* right) {
    if (left == nullptr || right == nullptr)
        throw std::invalid_argument("Both expressions has to be valid!");

    left_ = left;
    right_ = right;
}

BinaryOperation::BinaryOperation(const BinaryOperation& operation) {
    left_ = operation.left_->copy();
    right_ = operation.right_->copy();
}

BinaryOperation::BinaryOperation(BinaryOperation&& operation) {
    left_ = operation.left_;
    right_ = operation.right_;

    operation.left_ = nullptr;
    operation.right_ = nullptr;
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

UnaryOperation::UnaryOperation(const UnaryOperation& operation) {
    main_ = operation.main_->copy();   
}

UnaryOperation::UnaryOperation(UnaryOperation&& operation) {
    main_ = operation.main_;

    operation.main_ = nullptr;
}

UnaryOperation::~UnaryOperation() {
    delete main_;
}

std::string Add::to_string() const {
    std::ostringstream oss;
    oss << '(' << left_->to_string() << ')';
    oss << '+';
    oss << '(' << right_->to_string() << ')';

    return oss.str();
}

Expression* Add::differentiate(char var) const {
    return new Add{left_->differentiate(var), right_->differentiate(var)};
}

Expression* Add::copy() const {
    return new Add{left_->copy(), right_->copy()};
}

std::string Sub::to_string() const {
    std::ostringstream oss;
    oss << '(' << left_->to_string() << ')';
    oss << '-';
    oss << '(' << right_->to_string() << ')';

    return oss.str();
}

Expression* Sub::differentiate(char var) const {
    return new Sub{left_->differentiate(var), right_->differentiate(var)};
}

Expression* Sub::copy() const {
    return new Sub{left_->copy(), right_->copy()};
}

std::string Mul::to_string() const {
    std::ostringstream oss;
    oss << '(' << left_->to_string() << ')';
    oss << '*';
    oss << '(' << right_->to_string() << ')';

    return oss.str();
}

Expression* Mul::differentiate(char var) const {
    auto left = new Mul{left_->differentiate(var), right_->copy()};
    auto right = new Mul{left_->copy(), right_->differentiate(var)};
    return new Add{left, right};
}

Expression* Mul::copy() const {
    return new Mul{left_->copy(), right_->copy()};
}

std::string Div::to_string() const {
    std::ostringstream oss;
    oss << '(' << left_->to_string() << ')';
    oss << '/';
    oss << '(' << right_->to_string() << ')';

    return oss.str();
}

Expression* Div::differentiate(char var) const {
    auto left = new Mul{left_->differentiate(var), right_->copy()};
    auto right = new Mul{left_->copy(), right_->differentiate(var)};

    return new Div{new Sub{left, right}, new Mul{right_->copy(), right_->copy()}};
}

Expression* Div::copy() const {
    return new Div{left_->copy(), right_->copy()};
}

std::string Neg::to_string() const {
    std::ostringstream oss;
    oss << '-';
    oss << '(' << main_->to_string() << ')';

    return oss.str();
}

Expression* Neg::differentiate(char var) const {
    return new Neg{main_->differentiate(var)};
}

Expression* Neg::copy() const {
    return new Neg{main_->copy()};
}

Exp::Exp(int value) : UnaryOperation(new Value{value}) {}

std::string Exp::to_string() const {
    std::ostringstream oss;
    oss << "e^";
    oss << '(' << main_->to_string() << ')';

    return oss.str();
}

Expression* Exp::differentiate(char var) const {
    return new Mul{main_->differentiate(var), new Exp{main_->copy()}};
}

Expression* Exp::copy() const {
    return new Exp{main_->copy()};
}

Ln::Ln(int value) : UnaryOperation(new Value{value}) {}

std::string Ln::to_string() const {
    std::ostringstream oss;
    oss << "ln";
    oss << '(' << main_->to_string() << ')';

    return oss.str();
}

Expression* Ln::differentiate(char var) const {
    auto exp = new Div{new Value{1}, main_->copy()};
    return new Mul{main_->differentiate(var), exp};
}

Expression* Ln::copy() const {
    return new Ln{main_->copy()};
}

Value::Value() : value_(0) {}
Value::Value(int value) : value_(value) {}

std::string Value::to_string() const {
    return std::to_string(value_);
}

Expression* Value::differentiate(char var) const {
    return new Value;
}

Expression* Value::copy() const {
    return new Value{value_};
}

Variable::Variable(char name) {
    if (std::islower(name) == 0)
        throw std::invalid_argument("Name of variable has to be lowercase english letter!");
    
    name_ = name;
}

std::string Variable::to_string() const {
    return std::string{name_};
}

Expression* Variable::differentiate(char var) const {
    if (var == name_)
        return new Value{1};

    return new Value;
}

Expression* Variable::copy() const {
    return new Variable(name_);
}
