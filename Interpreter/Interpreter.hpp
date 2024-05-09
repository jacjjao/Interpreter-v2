#pragma once

#include "Expr.hpp"
#include "ASTVisitor.hpp"
#include "Environment.hpp"
#include <stdexcept>

class RuntimeError : public std::runtime_error 
{
public:
    RuntimeError(Token token, const char* err_msg);

private:
    Token token_;
};

class EnvList
{
public:
    EnvList();

    void enterBlock();

    void exitBlock();

    bool declare(const std::string& name, const Expr::r_type& val);

    std::optional<Expr::r_type> get(const std::string& name);

    bool set(const std::string& name, const Expr::r_type& val);

private:
    std::list<Environment> env_;
};

class Interpreter : ASTVisitor
{
public:
    Expr::r_type interpret(Expr& expr);

    Expr::r_type visit(Expr& expr) override;

    Expr::r_type visitBinaryExpr(BinaryExpr& expr) override;

    Expr::r_type visitUnaryExpr(UnaryExpr& expr) override;

    Expr::r_type visitGroupingExpr(GroupingExpr& expr) override;

    Expr::r_type visitNumberExpr(NumberExpr& expr) override;

    Expr::r_type visitStringExpr(StringExpr& expr) override;

    Expr::r_type visitBoolExpr(BoolExpr& expr) override;

    Expr::r_type visitNullExpr(NullExpr& expr) override;

    Expr::r_type visitDeclaration(Declaration& dec) override;

    Expr::r_type visitAssignment(Assignment& assign) override;

    Expr::r_type visitVariable(Variable& var) override;

    Expr::r_type visitBlock(BlockExpr& block) override;

    Expr::r_type visitIf(IfExpr& expr) override;

private:
    RuntimeError error(const Token& token, const std::string& err_msg);

    void checkSameTypeAndNotNull(const Token& token, const Expr::r_type& left, const Expr::r_type& right);
    void checkBoolOperand(const Token& token, const Expr::r_type& operand);
    void checkNumberOperand(const Token& token, const Expr::r_type& operand);
    void checkNumberOperand(const Token& token, const Expr::r_type& left, const Expr::r_type& right);
    void checkNumberOrStringOperand(const Token& token, const Expr::r_type& left, const Expr::r_type& right);

    EnvList env_;
};