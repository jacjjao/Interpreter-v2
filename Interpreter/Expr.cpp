#include "Expr.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> lhs, const Token& token, std::unique_ptr<Expr> rhs) :
    lhs_(std::move(lhs)),
    token_(token),
    rhs_(std::move(rhs))
{
}

double BinaryExpr::evaluate() const
{
    switch (token_.type)
    {
    case TokenType::Plus:
        return lhs_->evaluate() + rhs_->evaluate();

    case TokenType::Minus:
        return lhs_->evaluate() - rhs_->evaluate();

    case TokenType::Mul:
        return lhs_->evaluate() * rhs_->evaluate();

    case TokenType::Div:
        return lhs_->evaluate() / rhs_->evaluate();

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
    if (lhs_)
        lhs_->printTokenInfo(out);
    out << "Token Type: " << toString(token_.type) << "  str: " << token_.str << '\n';
    if (rhs_)
        rhs_->printTokenInfo(out);
    return out;
}

UnaryExpr::UnaryExpr(const Token& token, std::unique_ptr<Expr> rhs) :
    token_(token),
    rhs_(std::move(rhs))
{
}

double UnaryExpr::evaluate() const
{
    return -(rhs_->evaluate());
}

std::ostream& UnaryExpr::printTokenInfo(std::ostream& out) const
{
    out << "Token Type: " << toString(token_.type) << "  str: " << token_.str << '\n';
    if (rhs_)
        rhs_->printTokenInfo(out);
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

GroupingExpr::GroupingExpr(std::unique_ptr<Expr> expr) : 
    expr_(std::move(expr))
{
}

double GroupingExpr::evaluate() const
{
    return expr_->evaluate();
}

std::ostream& GroupingExpr::printTokenInfo(std::ostream& out) const
{
    return expr_->printTokenInfo(out);
}
