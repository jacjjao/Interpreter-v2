#include "ASTPrinter.hpp"
#include <iostream>
#include <format>

std::any ASTPrinter::visit(Expr& expr)
{
    return expr.accept(*this);
}

std::any ASTPrinter::visitBinaryExpr(BinaryExpr& expr)
{
    if (expr.lhs)
        visit(*expr.lhs);
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    if (expr.rhs)
        visit(*expr.rhs);
    return {};
}

std::any ASTPrinter::visitUnaryExpr(UnaryExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    if (expr.rhs)
        visit(*expr.rhs);
    return {};
}

std::any ASTPrinter::visitGroupingExpr(GroupingExpr& expr)
{
    return visit(*expr.expr);
}

std::any ASTPrinter::visitNumberExpr(NumberExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return {};
}
