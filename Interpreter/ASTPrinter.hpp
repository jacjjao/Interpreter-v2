#pragma once

#include "ASTVisitor.hpp"

class ASTPrinter : public ASTVisitor
{
public:
    void print(Expr& expr);

    Expr::r_type visit(Expr& expr) override;

    Expr::r_type visitBinaryExpr(BinaryExpr& expr) override;

    Expr::r_type visitUnaryExpr(UnaryExpr& expr) override;

    Expr::r_type visitGroupingExpr(GroupingExpr& expr) override;

    Expr::r_type visitNumberExpr(NumberExpr& expr) override;

    Expr::r_type visitStringExpr(StringExpr& expr) override;

    Expr::r_type visitBoolExpr(BoolExpr& expr) override;

    Expr::r_type visitNullExpr(NullExpr& expr) override;
};