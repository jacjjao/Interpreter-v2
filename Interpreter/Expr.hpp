#pragma once

#include "Token/Token.hpp"
#include <memory>
#include <any>

class ASTVisitor;

class Expr
{
public:
    virtual ~Expr() = default;

    virtual std::any accept(ASTVisitor& walker) = 0;
};

class BinaryExpr : public Expr
{
public:
    BinaryExpr(std::unique_ptr<Expr> leftExpr, const Token& token, std::unique_ptr<Expr> rightExpr);
    ~BinaryExpr() override = default;

    std::any accept(ASTVisitor& walker) override;

    const std::unique_ptr<Expr> lhs;
    const Token token;
    const std::unique_ptr<Expr> rhs;
};

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token& token, std::unique_ptr<Expr> rightExpr);
    ~UnaryExpr() override = default;

    std::any accept(ASTVisitor& walker) override;

    const Token token;
    const std::unique_ptr<Expr> rhs;
};

class GroupingExpr : public Expr
{
public:
    GroupingExpr(std::unique_ptr<Expr> op);
    ~GroupingExpr() override = default;

    std::any accept(ASTVisitor& walker) override;

    const std::unique_ptr<Expr> expr;
};

class NumberExpr : public Expr
{
public:
    NumberExpr(const Token& op);
    ~NumberExpr() override = default;

    std::any accept(ASTVisitor& walker) override;

    const double value;
    const Token token;
};