#pragma once

#include "Token/Token.hpp"
#include <span>
#include <stdexcept>
#include <vector>
#include <string>

class LexError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class Lexer
{
public:
    std::vector<Token> lexInput(const std::string& input);
    
private:
    void pushToken(std::vector<Token>& tokens, std::string str, const TokenType type);
    LexError error(int line, const std::string& err_msg);
};