#pragma once

#include "Expr.hpp"

class ASTVisitor
{
public:
    virtual ~ASTVisitor() = default;

    virtual Expr::r_type visit(Expr& expr) = 0;

    virtual Expr::r_type visitBinaryExpr(BinaryExpr& expr) = 0;

    virtual Expr::r_type visitUnaryExpr(UnaryExpr& expr) = 0;

    virtual Expr::r_type visitGroupingExpr(GroupingExpr& expr) = 0;

    virtual Expr::r_type visitNumberExpr(NumberExpr& expr) = 0;

    virtual Expr::r_type visitStringExpr(StringExpr& expr) = 0;

    virtual Expr::r_type visitBoolExpr(BoolExpr& expr) = 0;

    virtual Expr::r_type visitNullExpr(NullExpr& expr) = 0;
};