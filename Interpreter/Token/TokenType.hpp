#pragma once

#include <string>

enum class TokenType
{
    Number,
    Plus,
    Minus,
    Mul,
    Div,
    Negative
};

std::string toString(TokenType type);