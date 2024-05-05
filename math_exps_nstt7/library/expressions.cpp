#include "expressions.hpp"

BinaryOperation::BinaryOperation(Expression* left, Expression* right, char sym) {
    if (left == nullptr || right == nullptr)
        throw std::invalid_argument("Both expressions has to be valid!");

    left_ = left;
    right_ = right;
    sym_ = sym;
}

BinaryOperation::BinaryOperation(const BinaryOperation& operation) {
    left_ = operation.left_->copy();
    right_ = operation.right_->copy();
    sym_ = operation.sym_;
}

BinaryOperation::BinaryOperation(BinaryOperation&& operation) {
    left_ = operation.left_;
    right_ = operation.right_;
    sym_ = operation.sym_;

    operation.left_ = nullptr;
    operation.right_ = nullptr;
}

BinaryOperation::~BinaryOperation() {
    delete left_;
    delete right_;
}

std::string BinaryOperation::to_string() const {
    std::ostringstream stream;
    stream << '(' << left_->to_string() << ')';
    stream << sym_;
    stream << '(' << right_->to_string() << ')';

    return stream.str();
}

UnaryOperation::UnaryOperation(Expression* main, char sym) {
    if (main == nullptr)
        throw std::invalid_argument("Expression has to be valid!");
    
    main_ = main;
    sym_ = sym;
}

UnaryOperation::UnaryOperation(Expression* main) {
    if (main == nullptr)
        throw std::invalid_argument("Expression has to be valid!");

    main_ = main;
    sym_ = '\0';
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

std::string UnaryOperation::to_string() const {
    std::ostringstream stream;
    stream << sym_;
    stream << '(' << main_->to_string() << ')';

    return stream.str();
}

Add::Add(Expression* left, Expression* right) : BinaryOperation(left, right, '+') {}
Add::Add(const Add& ref) : BinaryOperation(ref) {}
Add::Add(Add&& ref) : BinaryOperation(ref) {}

Expression* Add::to_differentiated(char var) const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    return new Add{left_->to_differentiated(var), right_->to_differentiated(var)};
}

Expression* Add::copy() const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    return new Add{left_->copy(), right_->copy()};
}

Sub::Sub(Expression* left, Expression* right) : BinaryOperation(left, right, '-') {}
Sub::Sub(const Sub& ref) : BinaryOperation(ref) {}
Sub::Sub(Sub&& ref) : BinaryOperation(ref) {}

Expression* Sub::to_differentiated(char var) const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    return new Sub{left_->to_differentiated(var), right_->to_differentiated(var)};
}

Expression* Sub::copy() const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    return new Sub{left_->copy(), right_->copy()};
}

Mul::Mul(Expression* left, Expression* right) : BinaryOperation(left, right, '*') {}
Mul::Mul(const Mul& ref) : BinaryOperation(ref) {}
Mul::Mul(Mul&& ref) : BinaryOperation(ref) {}

Expression* Mul::to_differentiated(char var) const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    auto left = new Mul{left_->to_differentiated(var), right_->copy()};
    auto right = new Mul{left_->copy(), right_->to_differentiated(var)};
    return new Add{left, right};
}

Expression* Mul::copy() const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    return new Mul{left_->copy(), right_->copy()};
}

Div::Div(Expression* left, Expression* right) : BinaryOperation(left, right, '/') {}
Div::Div(const Div& ref) : BinaryOperation(ref) {}
Div::Div(Div&& ref) : BinaryOperation(ref) {}

Expression* Div::to_differentiated(char var) const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    auto left = new Mul{left_->to_differentiated(var), right_->copy()};
    auto right = new Mul{left_->copy(), right_->to_differentiated(var)};

    return new Div{new Sub{left, right}, new Mul{right_->copy(), right_->copy()}};
}

Expression* Div::copy() const {
    assert(left_ != nullptr);
    assert(right_ != nullptr);

    return new Div{left_->copy(), right_->copy()};
}

Neg::Neg(Expression* main) : UnaryOperation(main, '-') {}

Expression* Neg::to_differentiated(char var) const {
    assert(main_ != nullptr);
    return new Neg{main_->to_differentiated(var)};
}

Expression* Neg::copy() const {
    assert(main_ != nullptr);
    return new Neg{main_->copy()};
}

Exp::Exp(int value) : UnaryOperation(new Value{value}) {}

std::string Exp::to_string() const {
    assert(main_ != nullptr);

    std::ostringstream oss;
    oss << "e^";
    oss << '(' << main_->to_string() << ')';

    return oss.str();
}

Expression* Exp::to_differentiated(char var) const {
    assert(main_ != nullptr);
    return new Mul{main_->to_differentiated(var), new Exp{main_->copy()}};
}

Expression* Exp::copy() const {
    assert(main_ != nullptr);
    return new Exp{main_->copy()};
}

Ln::Ln(int value) : UnaryOperation(new Value{value}) {}

std::string Ln::to_string() const {
    assert(main_ != nullptr);

    std::ostringstream oss;
    oss << "ln";
    oss << '(' << main_->to_string() << ')';

    return oss.str();
}

Expression* Ln::to_differentiated(char var) const {
    assert(main_ != nullptr);
    return new Mul{main_->to_differentiated(var), new Div{new Value{1}, main_->copy()}};
}

Expression* Ln::copy() const {
    assert(main_ != nullptr);
    return new Ln{main_->copy()};
}

Value::Value(int value) : value_(value) {}

std::string Value::to_string() const {
    return std::to_string(value_);
}

Expression* Value::to_differentiated(char var) const {
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

Expression* Variable::to_differentiated(char var) const {
    if (var == name_)
        return new Value{1};

    return new Value{0};
}

Expression* Variable::copy() const {
    return new Variable{name_};
}
