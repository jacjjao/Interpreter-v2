#pragma once

#include "Token/Token.hpp"
#include <memory>
#include <optional>
#include <variant>

class ASTVisitor;

class Expr
{
public:
    using r_type = std::variant<std::monostate, bool, double, std::string>;

    virtual ~Expr() = default;

    virtual r_type accept(ASTVisitor& visitor) = 0;
};

class BinaryExpr : public Expr
{
public:
    BinaryExpr(std::unique_ptr<Expr> leftExpr, const Token& token, std::unique_ptr<Expr> rightExpr);
    ~BinaryExpr() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    const std::unique_ptr<Expr> lhs;
    const Token token;
    const std::unique_ptr<Expr> rhs;
};

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token& token, std::unique_ptr<Expr> rightExpr);
    ~UnaryExpr() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    const Token token;
    const std::unique_ptr<Expr> rhs;
};

class GroupingExpr : public Expr
{
public:
    GroupingExpr(std::unique_ptr<Expr> op);
    ~GroupingExpr() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    const std::unique_ptr<Expr> expr;
};

class NumberExpr : public Expr
{
public:
    NumberExpr(const Token& op);
    ~NumberExpr() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    const double value;
    const Token token;
};

class StringExpr : public Expr
{
public:
    StringExpr(const Token& op);
    ~StringExpr() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    const std::string& str() const;

    const Token token;
};

class BoolExpr : public Expr
{
public:
    BoolExpr(const Token& op);
    ~BoolExpr() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    const bool value;
    const Token token;
};

class NullExpr : public Expr
{
public:
    NullExpr(const Token& op);
    ~NullExpr() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    std::monostate value() const;
    
    const Token token;
};

class Declaration : public Expr
{
public:
    Declaration(const Token& name, std::unique_ptr<Expr> initializer);
    ~Declaration() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    Expr::r_type getInitVal(ASTVisitor& visitor);

    const Token name_;

private:
    const std::unique_ptr<Expr> initializer_;
};

class Assignment : public Expr
{
public:
    Assignment(const Token& name, std::unique_ptr<Expr> val);
    ~Assignment() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    Expr::r_type getVal(ASTVisitor& visitor);

    const Token name_;

private:
    const std::unique_ptr<Expr> val_;
};

class Variable : public Expr
{
public:
    Variable(const Token& name);
    ~Variable() override = default;

    Expr::r_type accept(ASTVisitor& visitor) override;

    const Token name_;
};