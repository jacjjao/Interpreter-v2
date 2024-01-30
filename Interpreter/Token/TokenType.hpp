#pragma once

#include <string>
#include <optional>

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

constexpr std::optional<char> toChar(TokenType type)
{
    switch (type)
    {
    case TokenType::Eoe:
        return '\n';
    }
    return std::nullopt;
}