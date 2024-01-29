#pragma once

#include <string>

enum class TokenType
{
    Number,
    Plus,
    Minus,
    Mul,
    Div,
    Negative,
    LeftParen,
    RightParen,
    Eof
};

std::string toString(TokenType type);