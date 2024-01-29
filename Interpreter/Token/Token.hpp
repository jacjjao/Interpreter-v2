#pragma once

#include "TokenType.hpp"
#include <string>

struct Token
{
    std::string str;
    TokenType type;
    int line;
};