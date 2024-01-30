#pragma once

#include "Token/Token.hpp"
#include <span>
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>

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
    std::string getWord(std::string_view input, size_t offset, char sep = ' ');

    int line_count_ = 0;

    inline static const std::unordered_map<std::string, TokenType> s_key_words = [] {
        std::unordered_map<std::string, TokenType> mp;
        mp.insert({ "true", TokenType::Bool });
        mp.insert({ "false", TokenType::Bool });
        return mp;
    }();
};