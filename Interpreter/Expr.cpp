#include "pch.hpp"
#include "Expr.hpp"
#include "ASTVisitor.hpp"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> leftExpr, const Token& op, std::unique_ptr<Expr> rightExpr) :
    lhs(std::move(leftExpr)),
    token(op),
    rhs(std::move(rightExpr))
{
}

Expr::r_type BinaryExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitBinaryExpr(*this);
}

UnaryExpr::UnaryExpr(const Token& op, std::unique_ptr<Expr> rightExpr) :
    token(op),
    rhs(std::move(rightExpr))
{
}
Expr::r_type UnaryExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitUnaryExpr(*this);
}

NumberExpr::NumberExpr(const Token& op) :
    token(op),
    value(std::stod(op.str))
{
}

Expr::r_type NumberExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitNumberExpr(*this);
}

GroupingExpr::GroupingExpr(std::unique_ptr<Expr> op) : 
    expr(std::move(op))
{
}

Expr::r_type GroupingExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitGroupingExpr(*this);
}

StringExpr::StringExpr(const Token& op) : 
    token(op)
{
}

Expr::r_type StringExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitStringExpr(*this);
}

const std::string& StringExpr::str() const
{
    return token.str;
}

BoolExpr::BoolExpr(const Token& op) : 
    token(op),
    value(op.str == "true")
{
}

Expr::r_type BoolExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitBoolExpr(*this);
}

NullExpr::NullExpr(const Token& op) : 
    token(op)
{
}

Expr::r_type NullExpr::accept(ASTVisitor& visitor)
{
    return visitor.visitNullExpr(*this);
}

std::monostate NullExpr::value() const
{
    return std::monostate();
}

Declaration::Declaration(const Token& name, std::unique_ptr<Expr> initializer) :
    name_(name),
    initializer_(std::move(initializer))
{
}

Expr::r_type Declaration::accept(ASTVisitor& visitor)
{
    return visitor.visitDeclaration(*this);
}

Expr::r_type Declaration::getInitVal(ASTVisitor& visitor)
{
    if (!initializer_) {
        return std::monostate{};
    }
    return visitor.visit(*initializer_);
}

Variable::Variable(const Token& name) : 
    name_(name)
{
}

Expr::r_type Variable::accept(ASTVisitor& visitor)
{
    return visitor.visitVariable(*this);
}
