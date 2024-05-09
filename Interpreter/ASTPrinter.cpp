#include "pch.hpp"
#include "ASTPrinter.hpp"

void ASTPrinter::print(Expr& expr)
{
    visit(expr);
}

Expr::r_type ASTPrinter::visit(Expr& expr)
{
    return expr.accept(*this);
}

Expr::r_type ASTPrinter::visitBinaryExpr(BinaryExpr& expr)
{
    if (expr.lhs)
        visit(*expr.lhs);
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    if (expr.rhs)
        visit(*expr.rhs);
    return {};
}

Expr::r_type ASTPrinter::visitUnaryExpr(UnaryExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    if (expr.rhs)
        visit(*expr.rhs);
    return {};
}

Expr::r_type ASTPrinter::visitGroupingExpr(GroupingExpr& expr)
{
    return visit(*expr.expr);
}

Expr::r_type ASTPrinter::visitNumberExpr(NumberExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return {};
}

Expr::r_type ASTPrinter::visitStringExpr(StringExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return {};
}

Expr::r_type ASTPrinter::visitBoolExpr(BoolExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return {};
}

Expr::r_type ASTPrinter::visitNullExpr(NullExpr& expr)
{
    std::cout << std::format("Token Type: {}  str: {}\n", toString(expr.token.type), expr.token.str);
    return {};
}

Expr::r_type ASTPrinter::visitDeclaration(Declaration& dec)
{
    std::cout << std::format("Token type: {}  name: {}\n", toString(TokenType::Declaration), dec.name_.str);
    return {};
}

Expr::r_type ASTPrinter::visitAssignment(Assignment& assign)
{
    std::cout << std::format("Token type: {}  name: {}\n", toString(TokenType::Assignment), assign.name_.str);
    return {};
}

Expr::r_type ASTPrinter::visitVariable(Variable& var)
{
    std::cout << std::format("Token Type: {}  name: {}\n", toString(TokenType::Identifier), var.name_.str);
    return {};
}

Expr::r_type ASTPrinter::visitBlock(BlockExpr&)
{
    std::cout << "New Block\n";
    return {};
}

Expr::r_type ASTPrinter::visitIf(IfExpr&)
{
    std::cout << "If block\n";
    return {};
}
