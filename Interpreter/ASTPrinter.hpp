#pragma once

#include "ASTVisitor.hpp"
#include <any>

class ASTPrinter : public ASTVisitor
{
public:
    virtual std::any visit(Expr& expr) override;

    virtual std::any visitBinaryExpr(BinaryExpr& expr) override;

    virtual std::any visitUnaryExpr(UnaryExpr& expr) override;

    virtual std::any visitGroupingExpr(GroupingExpr& expr) override;

    virtual std::any visitNumberExpr(NumberExpr& expr) override;
};