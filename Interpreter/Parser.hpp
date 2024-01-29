#pragma once

#include "Expr.hpp"
#include "Token/Token.hpp"
#include <span>
#include <memory>
#include <stdexcept>

class ParseError : public std::runtime_error
{
public:
    ParseError(const char* s) : std::runtime_error(s) {}
};

class Parser
{
public:
    Parser(std::span<Token> tokens);

    std::unique_ptr<Expr> parse();

private:
    ParseError error(const Token& token, const char* err_msg);

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> term();
	std::unique_ptr<Expr> factor();
	std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    void consume();
    void consume(TokenType type, const char* err_msg);
    Token previous() const;
    Token peek() const;
    bool match(std::initializer_list<TokenType> types);
    bool atEnd() const;

    std::span<Token> tokens_;
    size_t cur_;
};