#pragma once

#include "Expr.hpp"
#include <any>

class ASTVisitor
{
public:
    virtual std::any visit(Expr& expr) = 0;

    virtual std::any visitBinaryExpr(BinaryExpr& expr) = 0;

    virtual std::any visitUnaryExpr(UnaryExpr& expr) = 0;

    virtual std::any visitGroupingExpr(GroupingExpr& expr) = 0;

    virtual std::any visitNumberExpr(NumberExpr& expr) = 0;
};