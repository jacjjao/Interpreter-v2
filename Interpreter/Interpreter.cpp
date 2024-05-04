#include "pch.hpp"
#include "Interpreter.hpp"
#include "Lox.hpp"

void Interpreter::interpret(Expr& expr)
{
    try
    {
        Lox::printInterpretResult(visit(expr));
    }
    catch (const RuntimeError&)
    {
    }
}

Expr::r_type Interpreter::visit(Expr& expr)
{
    return expr.accept(*this);
}

Expr::r_type Interpreter::visitBinaryExpr(BinaryExpr& expr)
{
    auto lhs = visit(*expr.lhs);
    auto rhs = visit(*expr.rhs);

    switch (expr.token.type)
    {
    case TokenType::Plus:
        checkNumberOrStringOperand(expr.token, lhs, rhs);
        if (std::holds_alternative<double>(lhs))
            return std::get<double>(lhs) + std::get<double>(rhs);
        return std::get<std::string>(lhs) + std::get<std::string>(rhs);

    case TokenType::Minus:
        checkNumberOperand(expr.token, lhs, rhs);
        return std::get<double>(lhs) - std::get<double>(rhs);

    case TokenType::Mul:
        checkNumberOperand(expr.token, lhs, rhs);
        return std::get<double>(lhs) * std::get<double>(rhs);

    case TokenType::Div:
        checkNumberOperand(expr.token, lhs, rhs);
        return std::get<double>(lhs) / std::get<double>(rhs);

    case TokenType::NotEqual:
        return lhs != rhs;

    case TokenType::Equal:
        return lhs == rhs;

    case TokenType::GreaterEq:
        checkSameTypeAndNotNull(expr.token, lhs, rhs);
        return lhs >= rhs;

    case TokenType::LessEq:
        checkSameTypeAndNotNull(expr.token, lhs, rhs);
        return lhs <= rhs;

    case TokenType::Greater:
        checkSameTypeAndNotNull(expr.token, lhs, rhs);
        return lhs > rhs;

    case TokenType::Less:
        checkSameTypeAndNotNull(expr.token, lhs, rhs);
        return lhs < rhs;
    }
    throw error(expr.token, std::format("Invalid token: {} for binary expression.", toString(expr.token.type)).c_str());
}

Expr::r_type Interpreter::visitUnaryExpr(UnaryExpr& expr)
{
    auto v = visit(*expr.rhs);
    switch (expr.token.type)
    {
    case TokenType::Minus:
        checkNumberOperand(expr.token, v);
        return -std::get<double>(v);
    case TokenType::Bang:
        checkBoolOperand(expr.token, v);
        return !std::get<bool>(v);
    }
    throw error(expr.token, std::format("Invalid token: {} for unary expression.", toString(expr.token.type)).c_str());
}

Expr::r_type Interpreter::visitGroupingExpr(GroupingExpr& expr)
{
    return visit(*expr.expr);
}

Expr::r_type Interpreter::visitNumberExpr(NumberExpr& expr)
{
    return expr.value;
}

Expr::r_type Interpreter::visitStringExpr(StringExpr& expr)
{
    return expr.str();
}

Expr::r_type Interpreter::visitBoolExpr(BoolExpr& expr)
{
    return expr.value;
}

Expr::r_type Interpreter::visitNullExpr(NullExpr& expr)
{
    return expr.value();
}

Expr::r_type Interpreter::visitDeclaration(Declaration& dec)
{
    const auto val = dec.getInitVal(*this);
    if (!env_.declare(dec.name_.str, val))
        throw std::runtime_error(std::format("Variable {} have been declared!\n", dec.name_.str));
    return val;
}

Expr::r_type Interpreter::visitAssignment(Assignment& assign)
{
    const auto val = assign.getVal(*this);
    if (!env_.set(assign.name_.str, val))
        throw std::runtime_error(std::format("Variable {} does not exist!\n", assign.name_.str));
    return val;
}

Expr::r_type Interpreter::visitVariable(Variable& var)
{
    const auto v = env_.get(var.name_.str);
    if (!v) 
        throw std::runtime_error(std::format("Variable {} does not exist!\n", var.name_.str));
    return *v;
}

RuntimeError Interpreter::error(const Token& token, const std::string& err_msg)
{
    Lox::runtimeError(token.line, err_msg.c_str());
    return RuntimeError(token, err_msg.c_str());
}

void Interpreter::checkSameTypeAndNotNull(const Token& token, const Expr::r_type& left, const Expr::r_type& right)
{
    if (left.index() == right.index() && !std::holds_alternative<std::monostate>(left))
        return;
    throw error(token, "Operands must be the same type and not null.");
}

void Interpreter::checkBoolOperand(const Token& token, const Expr::r_type& operand)
{
    if (std::holds_alternative<bool>(operand))
        return;
    throw error(token, "Operand must be a boolean.");
}

void Interpreter::checkNumberOperand(const Token& token, const Expr::r_type& operand)
{
    if (std::holds_alternative<double>(operand))
        return;
    throw error(token, "Operand must be a number.");
}

void Interpreter::checkNumberOperand(const Token& token, const Expr::r_type& left, const Expr::r_type& right)
{
    if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
        return;
    throw error(token, "Operands must be numbers.");
}

void Interpreter::checkNumberOrStringOperand(const Token& token, const Expr::r_type& left, const Expr::r_type& right)
{
    if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
        return;
    if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right))
        return;
    throw error(token, "Operands must be numbers.");
}

RuntimeError::RuntimeError(Token token, const char* err_msg) :
    std::runtime_error(err_msg),
    token_(std::move(token))
{
}