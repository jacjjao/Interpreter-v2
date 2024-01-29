#pragma once

#include "Token/Token.hpp"
#include "Expr.hpp"

namespace Lox
{
    void report(int line, const char* err_msg);

    void error(int line, const char* err_msg);
}