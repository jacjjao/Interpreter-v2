#include "pch.hpp"
#include "ASTPrinter.hpp"

void ASTPrinter::print(Expr& expr)
{
    visit(expr);
}

std::optional<Expr::r_type> ASTPrinter::visit(Expr& expr)
{
    return expr.accept(*this);
}

std::optional<Expr::r_type> ASTPrinter::visitBinaryExpr(BinaryExpr& expr)
{
    if (expr.lhs)
        visit(*expr.lhs);
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    if (expr.rhs)
        visit(*expr.rhs);
    return std::nullopt;
}

std::optional<Expr::r_type> ASTPrinter::visitUnaryExpr(UnaryExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    if (expr.rhs)
        visit(*expr.rhs);
    return std::nullopt;
}

std::optional<Expr::r_type> ASTPrinter::visitGroupingExpr(GroupingExpr& expr)
{
    return visit(*expr.expr);
}

std::optional<Expr::r_type> ASTPrinter::visitNumberExpr(NumberExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return std::nullopt;
}

std::optional<Expr::r_type> ASTPrinter::visitStringExpr(StringExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return std::nullopt;
}

std::optional<Expr::r_type> ASTPrinter::visitBoolExpr(BoolExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return std::nullopt;
}
