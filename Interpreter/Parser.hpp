#pragma once

#include "Expr.hpp"
#include "Token/Token.hpp"
#include <span>
#include <memory>
#include <stdexcept>

class ParseError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class Parser
{
public:
    Parser(std::span<Token> tokens);

    std::vector<std::unique_ptr<Expr>> parse();

private:
    ParseError error(const Token& token, const char* err_msg);

    std::unique_ptr<Expr> statement();
    std::unique_ptr<Expr> declaration();
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> assignment();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
	std::unique_ptr<Expr> factor();
	std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    Token consume();
    Token consume(TokenType type, const char* err_msg);
    Token previous() const;
    Token peek() const;
    bool match(std::initializer_list<TokenType> types);
    bool atEnd() const;

    const std::span<Token> tokens_;
    size_t cur_;
};