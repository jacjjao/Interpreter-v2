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
    case TokenType::Eoe:
        return "Eoe";
    case TokenType::GreaterEq:
        return "GreaterEq";
    case TokenType::LessEq:
        return "LessEq";
    case TokenType::Equal:
        return "Equal";
    case TokenType::NotEqual:
        return "NotEqual";
    case TokenType::Greater:
        return "Greater";
    case TokenType::Less:
        return "Less";
    case TokenType::Null:
        return "Null";
    default:
        throw std::invalid_argument{ "Invalid token type" };
    }
}
