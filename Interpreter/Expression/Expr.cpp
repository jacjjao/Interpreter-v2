#include "Expr.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

BinaryExpr::BinaryExpr(const Token& token) : 
    token_(token)
{
}

double BinaryExpr::evaluate() const
{
    switch (token_.type)
    {
    case TokenType::Plus:
        return lhs->evaluate() + rhs->evaluate();

    case TokenType::Minus:
        return lhs->evaluate() - rhs->evaluate();

    case TokenType::Mul:
        return lhs->evaluate() * rhs->evaluate();

    case TokenType::Div:
        return lhs->evaluate() / rhs->evaluate();

    default:
    {
        std::stringstream ss;
        ss << "Invalid token type: " << toString(token_.type) << " for binary expression.";
        throw std::invalid_argument(std::move(ss).str());
    }
    }
}

std::ostream& BinaryExpr::printTokenInfo(std::ostream& out) const
{
    if (lhs)
        lhs->printTokenInfo(out);
    out << "Token Type: " << toString(token_.type) << "  str: " << token_.str << '\n';
    if (rhs)
        rhs->printTokenInfo(out);
    return out;
}

UnaryExpr::UnaryExpr(const Token& token) : 
    token_(token)
{
}

double UnaryExpr::evaluate() const
{
    return -(rhs->evaluate());
}

std::ostream& UnaryExpr::printTokenInfo(std::ostream& out) const
{
    out << "Token Type: " << toString(token_.type) << "  str: " << token_.str << '\n';
    if (rhs)
        rhs->printTokenInfo(out);
    return out;
}

NumberExpr::NumberExpr(const Token& token) : 
    token_(token)
{
    value_ = std::stod(token_.str);
}

double NumberExpr::evaluate() const
{
    return value_;
}

std::ostream& NumberExpr::printTokenInfo(std::ostream& out) const
{
    out << "Token Type: " << toString(token_.type) << "  str: " << token_.str << '\n';
    return out;
}
