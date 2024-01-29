#include "ASTWalker.hpp"
#include <sstream>

std::any ASTWalker::visit(Expr& expr)
{
    return expr.accept(*this);
}

std::any ASTWalker::visitBinaryExpr(BinaryExpr& expr)
{
    switch (expr.token.type)
    {
    case TokenType::Plus:
        return std::any_cast<double>(visit(*expr.lhs)) + std::any_cast<double>(visit(*expr.rhs));

    case TokenType::Minus:
        return std::any_cast<double>(visit(*expr.lhs)) - std::any_cast<double>(visit(*expr.rhs));

    case TokenType::Mul:
        return std::any_cast<double>(visit(*expr.lhs)) * std::any_cast<double>(visit(*expr.rhs));

    case TokenType::Div:
        return std::any_cast<double>(visit(*expr.lhs)) / std::any_cast<double>(visit(*expr.rhs));

    default:
    {
        std::stringstream ss;
        ss << "Invalid token type: " << toString(expr.token.type) << " for binary expression.";
        throw std::invalid_argument(std::move(ss).str());
    }
    }
}

std::any ASTWalker::visitUnaryExpr(UnaryExpr& expr)
{
    return -std::any_cast<double>(visit(*expr.rhs));
}

std::any ASTWalker::visitGroupingExpr(GroupingExpr& expr)
{
    return visit(*expr.expr);
}

std::any ASTWalker::visitNumberExpr(NumberExpr& expr)
{
    return expr.value;
}
