#pragma once

#include <string>

enum class TokenType : char
{
    Number,
    Plus,
    Minus,
    Mul,
    Div,
    Negative,
    LeftParen,
    RightParen,
    String,
    Eoe = '\n'
};

std::string toString(TokenType type);