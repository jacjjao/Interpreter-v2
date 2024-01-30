#pragma once

#include "Token/Token.hpp"
#include <span>
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>

class LexError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class Lexer
{
public:
    std::vector<Token> lexInput(std::string_view input);
    
private:
    void pushToken(std::vector<Token>& tokens, std::string str, const TokenType type);
    LexError error(int line, const std::string& err_msg);

    int line_count_ = 0;
};