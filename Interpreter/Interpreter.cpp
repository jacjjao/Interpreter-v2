#include "Interpreter.hpp"
#include <format>

std::optional<Expr::r_type> Interpreter::interpret(Expr& expr)
{
    try
    {
        return visit(expr);
    }
    catch (const RuntimeError& e)
    {
        // TODO
    }
}

std::optional<Expr::r_type> Interpreter::visit(Expr& expr)
{
    return expr.accept(*this);
}

std::optional<Expr::r_type> Interpreter::visitBinaryExpr(BinaryExpr& expr)
{
    auto lhs = visit(*expr.lhs);
    auto rhs = visit(*expr.rhs);

    switch (expr.token.type)
    {
    case TokenType::Plus:
        checkNumberOrStringOperand(expr.token, lhs, rhs);
        if (std::holds_alternative<double>(*lhs))
            return std::get<double>(*lhs) + std::get<double>(*rhs);
        return std::get<std::string>(*lhs) + std::get<std::string>(*rhs);

    case TokenType::Minus:
        checkNumberOperand(expr.token, lhs, rhs);
        return std::get<double>(*lhs) - std::get<double>(*rhs);

    case TokenType::Mul:
        checkNumberOperand(expr.token, lhs, rhs);
        return std::get<double>(*lhs) * std::get<double>(*rhs);

    case TokenType::Div:
        checkNumberOperand(expr.token, lhs, rhs);
        return std::get<double>(*lhs) / std::get<double>(*rhs);
    }
    throw RuntimeError(expr.token, std::format("Invalid token type: {} for binary expression.", toString(expr.token.type)).c_str());
}

std::optional<Expr::r_type> Interpreter::visitUnaryExpr(UnaryExpr& expr)
{
    auto v = visit(*expr.rhs);
    switch (expr.token.type)
    {
    case TokenType::Negative:
        checkNumberOperand(expr.token, v);
        return -std::get<double>(*v);
    }
    throw RuntimeError(expr.token, std::format("Invalid token type: {} for unary expression.", toString(expr.token.type)).c_str());
}

std::optional<Expr::r_type> Interpreter::visitGroupingExpr(GroupingExpr& expr)
{
    return visit(*expr.expr);
}

std::optional<Expr::r_type> Interpreter::visitNumberExpr(NumberExpr& expr)
{
    return expr.value;
}

void Interpreter::checkNumberOperand(const Token& token, const std::optional<Expr::r_type>& operand)
{
    if (operand && std::holds_alternative<double>(*operand))
        return;
    throw RuntimeError(token, "Operand must be a number.");
}

void Interpreter::checkNumberOperand(const Token& token, const std::optional<Expr::r_type>& left, const std::optional<Expr::r_type>& right)
{
    if (left && std::holds_alternative<double>(*left) && right && std::holds_alternative<double>(*right))
        return;
    throw RuntimeError(token, "Operands must be numbers.");
}

void Interpreter::checkNumberOrStringOperand(const Token& token, const std::optional<Expr::r_type>& left, const std::optional<Expr::r_type>& right)
{
    if (left && right)
    {
        if (std::holds_alternative<double>(*left) && std::holds_alternative<double>(*right))
            return;
        if (std::holds_alternative<std::string>(*left) && std::holds_alternative<std::string>(*right))
            return;
    }
    throw RuntimeError(token, "Operands must be numbers.");
}

RuntimeError::RuntimeError(Token token, const char* err_msg) :
    std::runtime_error(err_msg),
    token_(std::move(token))
{
}