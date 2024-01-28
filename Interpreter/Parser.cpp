#include "Parser.hpp"
#include <cassert>
#include <stdexcept>
#include <iostream>

Parser::Parser(std::span<Token> tokens) : 
    tokens_(tokens),
    cur_(0)
{
}

std::unique_ptr<Expr> Parser::parse()
{
    return expression();
}

std::unique_ptr<Expr> Parser::expression()
{
    return term();
}

std::unique_ptr<Expr> Parser::term()
{
    auto expr = factor();
    while (match({ TokenType::Plus, TokenType::Minus }))
    {
        auto op = previous();
        auto rhs = factor();
        expr = std::unique_ptr<Expr>(new BinaryExpr(std::move(expr), op, std::move(rhs)));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::factor()
{
    auto expr = unary();
    while (match({ TokenType::Mul, TokenType::Div }))
    {
        auto op = previous();
        auto rhs = unary();
        expr = std::unique_ptr<Expr>(new BinaryExpr(std::move(expr), op, std::move(rhs)));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::unary()
{
    while (match({ TokenType::Negative }))
    {
        auto op = previous();
        auto rhs = unary();
        return std::unique_ptr<Expr>(new UnaryExpr(op, std::move(rhs)));
    }
    return primary();
}

std::unique_ptr<Expr> Parser::primary()
{
    if (match({ TokenType::Number }))
        return std::unique_ptr<Expr>(new NumberExpr(previous()));
    if (match({ TokenType::LeftParen }))
    {
        auto expr = expression();
        consume(TokenType::RightParen, "Cannot match parentheses");
        return std::unique_ptr<Expr>(new GroupingExpr(std::move(expr)));
    }
    throw std::runtime_error("Cannot match primary");
}

void Parser::consume()
{
    ++cur_;
}

void Parser::consume(TokenType type, const std::string& err_msg)
{
    if (atEnd() || peek().type != type)
        throw std::runtime_error(err_msg);
    else 
        consume();
}

Token Parser::previous() const
{
    assert(cur_ > 0);
    return tokens_[cur_ - 1];
}

Token Parser::peek() const
{
    assert(cur_ < tokens_.size());
    return tokens_[cur_];
}

bool Parser::match(std::initializer_list<TokenType> types)
{
    for (const auto& type : types)
        if (!atEnd() && peek().type == type)
        {
            consume();
            return true;
        }
    return false;
}

bool Parser::atEnd() const
{
    return cur_ >= tokens_.size();
}
