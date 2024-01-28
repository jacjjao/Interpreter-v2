#pragma once

#include "Expr.hpp"
#include "Token/Token.hpp"
#include <span>
#include <memory>

class Parser
{
public:
    Parser(std::span<Token> tokens);

    std::unique_ptr<Expr> parse();

private:
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> term();
	std::unique_ptr<Expr> factor();
	std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    void consume();
    void consume(TokenType type, const std::string& err_msg);
    Token previous() const;
    Token peek() const;
    bool match(std::initializer_list<TokenType> types);
    bool atEnd() const;

    std::span<Token> tokens_;
    size_t cur_;
};