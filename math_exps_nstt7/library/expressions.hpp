#pragma once

#include <sstream>
#include <string>

#include <cctype>
#include <cassert>

#include <stdexcept>

struct Expression {
    // Do I need virtual dtor here?
    // Compiler warns that abstract class should have virtual destructor
    
    // So I made a virtual dtor as a default
    // Because unary/binary have their own dtors, Val/Var dont need dtor

    virtual ~Expression() = default;

    virtual std::string to_string() const = 0;
    virtual Expression* to_differentiated(char var) const = 0;

    // A deep copy of expression
    virtual Expression* copy() const = 0;

    /// @todo think about implementing this method
    // It's pretty hard btw
    // virtual void simplify() = 0;
};

/*
--------------------------------------
    My hirerarchy looks like this

    EXPRESSION
        |
        BINARY_OPERATION
        |   |
        |   ADD
        |   SUB
        |   MUL
        |   DIV
        |
        UNARY_OPERATION
        |   |
        |   NEG
        |   EXP
        |
        VALUE
        |
        VARIABLE
--------------------------------------
*/

class BinaryOperation : public Expression {
    public:
    BinaryOperation() = delete;

    BinaryOperation(Expression* left, Expression* right, char sym);
    BinaryOperation(Expression* left, Expression* right);
    
    BinaryOperation(const BinaryOperation& operation);
    BinaryOperation(BinaryOperation&& operation);

    virtual ~BinaryOperation();

    virtual std::string to_string() const;

    protected:
    Expression* left_;
    Expression* right_;
    char sym_;
};

class UnaryOperation : public Expression {
    public:
    UnaryOperation() = delete;

    UnaryOperation(Expression* expression, char sym);
    explicit UnaryOperation(Expression* expression);
    
    UnaryOperation(const UnaryOperation& operation);
    UnaryOperation(UnaryOperation&& operation);

    virtual ~UnaryOperation();

    virtual std::string to_string() const;

    protected:
    Expression* main_;
    char sym_;
};

class Add : public BinaryOperation {
    public:
    Add(Expression* left, Expression* right);
    Add(const Add& operation);
    Add(Add&& operation);

    Expression* to_differentiated(char var) const;
    Expression* copy() const;
};

class Sub : public BinaryOperation {
    public:
    Sub(Expression* left, Expression* right);
    Sub(const Sub& operation);
    Sub(Sub&& operation);

    Expression* to_differentiated(char var) const;
    Expression* copy() const;
};

class Mul : public BinaryOperation {
    public:
    Mul(Expression* left, Expression* right);
    Mul(const Mul& operation);
    Mul(Mul&& operation);

    Expression* to_differentiated(char var) const;
    Expression* copy() const;
};

class Div : public BinaryOperation {
    public:
    Div(Expression* left, Expression* right);
    Div(const Div& operation);
    Div(Div&& operation);

    Expression* to_differentiated(char var) const;
    Expression* copy() const;
};

class Neg : public UnaryOperation {
    public:
    Neg(Expression* main);
    Neg(const Neg& operation);
    Neg(Neg&& operation);

    Expression* to_differentiated(char var) const;
    Expression* copy() const;
};

class Exp : public UnaryOperation {
    public:
    using UnaryOperation::UnaryOperation;

    explicit Exp(int value);

    std::string to_string() const;
    Expression* to_differentiated(char var) const;
    Expression* copy() const;
};

class Ln : public UnaryOperation {
    public:
    using UnaryOperation::UnaryOperation;

    explicit Ln(int value);

    std::string to_string() const;
    Expression* to_differentiated(char var) const;
    Expression* copy() const;
};

class Value : public Expression {
    public:
    Value() = default;

    Value(int value);

    Value(const Value& value) = default;
    Value(Value&& value) = default;

    ~Value() = default;

    std::string to_string() const;
    Expression* to_differentiated(char var) const;
    Expression* copy() const;

    private:
    int value_ = 0;
};

class Variable : public Expression {
    public:
    Variable() = delete;
    
    Variable(char name);

    Variable(const Variable& variable) = default;
    Variable(Variable&& variable) = default;

    ~Variable() = default;

    std::string to_string() const;
    Expression* to_differentiated(char var) const;
    Expression* copy() const;

    private:
    char name_;
};
