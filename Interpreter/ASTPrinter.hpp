#pragma once

#include "ASTVisitor.hpp"

class ASTPrinter : public ASTVisitor
{
public:
    void print(Expr& expr);

    virtual std::optional<Expr::r_type> visit(Expr& expr) override;

    virtual std::optional<Expr::r_type> visitBinaryExpr(BinaryExpr& expr) override;

    virtual std::optional<Expr::r_type> visitUnaryExpr(UnaryExpr& expr) override;

    virtual std::optional<Expr::r_type> visitGroupingExpr(GroupingExpr& expr) override;

    virtual std::optional<Expr::r_type> visitNumberExpr(NumberExpr& expr) override;

    virtual std::optional<Expr::r_type> visitStringExpr(StringExpr& expr) override;
};