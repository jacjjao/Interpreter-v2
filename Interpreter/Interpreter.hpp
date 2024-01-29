#pragma once

#include "Expr.hpp"
#include "ASTVisitor.hpp"
#include <stdexcept>

class RuntimeError : public std::runtime_error 
{
public:
    RuntimeError(Token token, const char* err_msg);

private:
    Token token_;
};

class Interpreter : ASTVisitor
{
public:
    std::optional<Expr::r_type> interpret(Expr& expr);

    std::optional<Expr::r_type> visit(Expr& expr) override;

    std::optional<Expr::r_type> visitBinaryExpr(BinaryExpr& expr) override;

    std::optional<Expr::r_type> visitUnaryExpr(UnaryExpr& expr) override;

    std::optional<Expr::r_type> visitGroupingExpr(GroupingExpr& expr) override;

    std::optional<Expr::r_type> visitNumberExpr(NumberExpr& expr) override;

private:
    void checkNumberOperand(const Token& token, const std::optional<Expr::r_type>& operand);
    void checkNumberOperand(const Token& token, const std::optional<Expr::r_type>& left, const std::optional<Expr::r_type>& right);
    void checkNumberOrStringOperand(const Token& token, const std::optional<Expr::r_type>& left, const std::optional<Expr::r_type>& right);
};