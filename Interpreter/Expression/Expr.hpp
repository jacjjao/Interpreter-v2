#pragma once

#include "Token/Token.hpp"
#include <memory>

class Expr
{
public:
    virtual double evaluate() const = 0;
    virtual ~Expr() = default;

    virtual std::ostream& printTokenInfo(std::ostream& out) const = 0;
};

class BinaryExpr : public Expr
{
public:
    BinaryExpr(const Token& token);
    ~BinaryExpr() override = default;

    double evaluate() const override;

    std::ostream& printTokenInfo(std::ostream& out) const override;

    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;

private:
    Token token_;
};

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token& token);
    ~UnaryExpr() override = default;

    double evaluate() const override;

    std::ostream& printTokenInfo(std::ostream& out) const override;

    std::unique_ptr<Expr> rhs;

private:
    Token token_;
};

class NumberExpr : public Expr
{
public:
    NumberExpr(const Token& token);
    ~NumberExpr() override = default;

    double evaluate() const override;

    std::ostream& printTokenInfo(std::ostream& out) const override;

private:
    double value_;
    Token token_;
};