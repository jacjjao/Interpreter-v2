#include "pch.hpp"
#include "Parser.hpp"
#include "Lox.hpp"

Parser::Parser(std::span<Token> tokens) : 
    tokens_(tokens),
    cur_(0)
{
}

ParseError Parser::error(const Token& token, const char* err_msg)
{
    Lox::error(token.line, err_msg);
    return ParseError(err_msg);
}

std::vector<std::unique_ptr<Expr>> Parser::parse()
{
    std::vector<std::unique_ptr<Expr>> exprs;
    try
    {
        while (!atEnd())
            exprs.push_back(statement());
        return exprs;
    }
    catch (const ParseError&)
    {
        return {};
    }
}

std::unique_ptr<Expr> Parser::statement()
{
    if (match({ TokenType::Declaration }))
    {
        auto name = consume(TokenType::Identifier, "Expect identifier");
        
        std::unique_ptr<Expr> initializer = nullptr;
        if (match({ TokenType::Assignment }))
        {
            initializer = expression();
        }
        return std::unique_ptr<Expr>(new Declaration(name, std::move(initializer)));
    }
    return expression(); 
}

std::unique_ptr<Expr> Parser::expression()
{
    return equality();
}

std::unique_ptr<Expr> Parser::equality()
{
    auto expr = comparison();
    while (match({ TokenType::Equal, TokenType::NotEqual }))
    {
        auto op = previous();
        auto rhs = comparison();
        expr = std::unique_ptr<Expr>(new BinaryExpr(std::move(expr), op, std::move(rhs)));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::comparison()
{
    auto expr = term();
    while (match({ TokenType::Greater, TokenType::GreaterEq, TokenType::Less, TokenType::LessEq }))
    {
        auto op = previous();
        auto rhs = term();
        expr = std::unique_ptr<Expr>(new BinaryExpr(std::move(expr), op, std::move(rhs)));
    }
    return expr;
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
    while (match({ TokenType::Minus, TokenType::Bang }))
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
    if (match({ TokenType::String }))
        return std::unique_ptr<Expr>(new StringExpr(previous()));
    if (match({ TokenType::Bool }))
        return std::unique_ptr<Expr>(new BoolExpr(previous()));
    if (match({ TokenType::Null }))
        return std::unique_ptr<Expr>(new NullExpr(previous()));
    if (match({ TokenType::Identifier }))
        return std::unique_ptr<Expr>(new Variable(previous()));
    if (match({ TokenType::LeftParen }))
    {
        auto expr = expression();
        consume(TokenType::RightParen, "Cannot match parentheses");
        return std::unique_ptr<Expr>(new GroupingExpr(std::move(expr)));
    }
    throw error(peek(), "Expect expression.");
}

Token Parser::consume()
{
    return tokens_[cur_++];
}

Token Parser::consume(TokenType type, const char* err_msg)
{
    if (atEnd() || peek().type != type)
        throw error(peek(), err_msg);
    else 
        return consume();
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
    return cur_ >= tokens_.size() || peek().type == TokenType::Eoe;
}
