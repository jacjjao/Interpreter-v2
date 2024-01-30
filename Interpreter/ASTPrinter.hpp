#pragma once

#include "ASTVisitor.hpp"

class ASTPrinter : public ASTVisitor
{
public:
    void print(Expr& expr);

    std::optional<Expr::r_type> visit(Expr& expr) override;

    std::optional<Expr::r_type> visitBinaryExpr(BinaryExpr& expr) override;

    std::optional<Expr::r_type> visitUnaryExpr(UnaryExpr& expr) override;

    std::optional<Expr::r_type> visitGroupingExpr(GroupingExpr& expr) override;

    std::optional<Expr::r_type> visitNumberExpr(NumberExpr& expr) override;

    std::optional<Expr::r_type> visitStringExpr(StringExpr& expr) override;

    std::optional<Expr::r_type> visitBoolExpr(BoolExpr& expr) override;
};