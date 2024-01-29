#include "Expr.hpp"
#include "ASTVisitor.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> leftExpr, const Token& op, std::unique_ptr<Expr> rightExpr) :
    lhs(std::move(leftExpr)),
    token(op),
    rhs(std::move(rightExpr))
{
}

std::optional<Expr::r_type> BinaryExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitBinaryExpr(*this);
}

UnaryExpr::UnaryExpr(const Token& op, std::unique_ptr<Expr> rightExpr) :
    token(op),
    rhs(std::move(rightExpr))
{
}
std::optional<Expr::r_type> UnaryExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitUnaryExpr(*this);
}

NumberExpr::NumberExpr(const Token& op) :
    token(op),
    value(std::stod(op.str))
{
}

std::optional<Expr::r_type> NumberExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitNumberExpr(*this);
}

GroupingExpr::GroupingExpr(std::unique_ptr<Expr> op) : 
    expr(std::move(op))
{
}

std::optional<Expr::r_type> GroupingExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitGroupingExpr(*this);
}
