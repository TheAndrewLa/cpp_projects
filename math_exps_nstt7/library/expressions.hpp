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
    virtual Expression* differentiate(char var) const = 0;

    // A deep copy of expression
    virtual Expression* copy() const = 0;

    /// @todo think about implementing this method
    // It's pretty hard btw
    // virtual void simplify() = 0;
};

/*-------------------------------------
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
--------------------------------------*/

class BinaryOperation : public Expression {
    public:
    BinaryOperation() = delete;

    BinaryOperation(Expression* left, Expression* right);
    
    BinaryOperation(const BinaryOperation& operation);
    BinaryOperation(BinaryOperation&& operation);

    virtual ~BinaryOperation();

    protected:
    Expression* left_;
    Expression* right_;
};

class UnaryOperation : public Expression {
    public:
    UnaryOperation() = delete;

    explicit UnaryOperation(Expression* expression);
    
    UnaryOperation(const UnaryOperation& operation);
    UnaryOperation(UnaryOperation&& operation);

    virtual ~UnaryOperation();

    protected:
    Expression* main_;
};

class Add : public BinaryOperation {
    public:
    using BinaryOperation::BinaryOperation;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;
};

class Sub : public BinaryOperation {
    public:
    using BinaryOperation::BinaryOperation;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;
};

class Mul : public BinaryOperation {
    public:
    using BinaryOperation::BinaryOperation;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;
};

class Div : public BinaryOperation {
    public:
    using BinaryOperation::BinaryOperation;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;
};

class Neg : public UnaryOperation {
    public:
    using UnaryOperation::UnaryOperation;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;
};

class Exp : public UnaryOperation {
    public:
    using UnaryOperation::UnaryOperation;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;
};

class Value : public Expression {
    public:
    Value();

    Value(float value);
    
    Value(const Value& value) = default;
    Value(Value&& value) = default;

    ~Value() = default;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;

    private:
    float value_;
};

class Variable : public Expression {
    public:
    Variable() = delete;
    
    Variable(char name);

    Variable(const Variable& variable) = default;
    Variable(Variable&& variable) = default;

    ~Variable() = default;

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
    virtual Expression* copy() const;

    private:
    char name_;
};
