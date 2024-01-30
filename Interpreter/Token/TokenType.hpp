#pragma once

#include <string>

enum class TokenType
{
    Eoe,
    Number,
    Plus,
    Minus,
    Mul,
    Div,
    Negative,
    LeftParen,
    RightParen,
    String,
    Bool,
    Bang
};

std::string toString(TokenType type);

constexpr char toChar(TokenType type)
{
    switch (type)
    {
    case TokenType::Eoe:
        return '\n';
    }
    throw std::invalid_argument(std::format("Cannot map {} to char", toString(type)));
}