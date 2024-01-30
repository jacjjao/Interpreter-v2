#include "pch.hpp"
#include "TokenType.hpp"

std::string toString(TokenType type)
{ 
    switch (type)
    {
    case TokenType::Number:
        return "Number";
    case TokenType::Plus:
        return "Plus";
    case TokenType::Minus:
        return "Minus";
    case TokenType::Mul:
        return "Mul";
    case TokenType::Div:
        return "Div";
    case TokenType::Negative:
        return "Negative";
    case TokenType::LeftParen:
        return "LeftParen";
    case TokenType::RightParen:
        return "RightParen";
    case TokenType::String:
        return "String";
    case TokenType::Bool:
        return "Bool";
    case TokenType::Bang:
        return "Bang";
    default:
        throw std::invalid_argument{ "Invalid token type" };
    }
}
