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
    BinaryExpr(std::unique_ptr<Expr> lhs, const Token& token, std::unique_ptr<Expr> rhs);
    ~BinaryExpr() override = default;

    double evaluate() const override;

    std::ostream& printTokenInfo(std::ostream& out) const override;

private:
    std::unique_ptr<Expr> lhs_;
    Token token_;
    std::unique_ptr<Expr> rhs_;
};

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token& token, std::unique_ptr<Expr> rhs);
    ~UnaryExpr() override = default;

    double evaluate() const override;

    std::ostream& printTokenInfo(std::ostream& out) const override;

private:
    Token token_;
    std::unique_ptr<Expr> rhs_;
};

class GroupingExpr : public Expr
{
public:
    GroupingExpr(std::unique_ptr<Expr> expr);
    ~GroupingExpr() override = default;

    double evaluate() const override;

    std::ostream& printTokenInfo(std::ostream& out) const override;

private:
    std::unique_ptr<Expr> expr_;
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