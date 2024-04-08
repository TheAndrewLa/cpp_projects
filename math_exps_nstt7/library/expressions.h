#pragma once

#include <sstream>
#include <string>

#include <stdexcept>

struct Expression {
    // Do we need it here?
    // Compiler warns that abstract class should have virtual destructor
    virtual ~Expression() = default;

    virtual std::string to_string() const = 0;
    virtual Expression* differentiate(char var) const = 0;
    
    /// @todo think about implementing this method
    // virtual void simplify() = 0;
};

class BinaryOperation : public Expression {
    public:
    BinaryOperation(Expression* left, Expression* right);
    virtual ~BinaryOperation();

    protected:
    Expression* left_;
    Expression* right_;
};

class UnaryOperation : public Expression {
    public:
    explicit UnaryOperation(Expression* expression);
    virtual ~UnaryOperation();

    protected:
    Expression* main_;
};

class Add : public BinaryOperation {
    public:
    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
};

class Sub : public BinaryOperation {
    public:
    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
};

class Mul : public BinaryOperation {
    public:
    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
};

class Div : public BinaryOperation {
    public:
    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
};

class Neg : public UnaryOperation {
    public:
    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
};

class Exp : public UnaryOperation {
    public:
    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;
};

class Value : Expression {
    public:
    Value(float val);

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;

    private:
    float value_;
};

class Variable : Expression {
    public:
    Variable(char name);

    virtual std::string to_string() const;
    virtual Expression* differentiate(char var) const;

    private:
    char name_;
};
