#pragma once

#include "Expr.hpp"
#include "ASTVisitor.hpp"

class ASTWalker : ASTVisitor
{
public:
    std::any visit(Expr& expr) override;

    std::any visitBinaryExpr(BinaryExpr& expr) override;

    std::any visitUnaryExpr(UnaryExpr& expr) override;

    std::any visitGroupingExpr(GroupingExpr& expr) override;

    std::any visitNumberExpr(NumberExpr& expr) override;
};