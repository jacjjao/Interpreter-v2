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

    std::optional<Expr::r_type> visitStringExpr(StringExpr& expr) override;

    std::optional<Expr::r_type> visitBoolExpr(BoolExpr& expr) override;

private:
    RuntimeError error(const Token& token, const std::string& err_msg);

    void checkHaveValue(const Token& token, const std::optional<Expr::r_type>& left, const std::optional<Expr::r_type>& right);
    void checkBoolOperand(const Token& token, const std::optional<Expr::r_type>& operand);
    void checkNumberOperand(const Token& token, const std::optional<Expr::r_type>& operand);
    void checkNumberOperand(const Token& token, const std::optional<Expr::r_type>& left, const std::optional<Expr::r_type>& right);
    void checkNumberOrStringOperand(const Token& token, const std::optional<Expr::r_type>& left, const std::optional<Expr::r_type>& right);
};