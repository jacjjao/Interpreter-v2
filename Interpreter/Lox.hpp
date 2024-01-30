#pragma once

#include "Token/Token.hpp"
#include "Expr.hpp"

class Lox
{
public:
    static void report(int line, const char* err_msg);

    static void error(int line, const char* err_msg);

    static void runtimeError(int line, const char* err_msg);

    static bool hadRuntimeErr();

    static void printInterpretResult(const Expr::r_type& result);

private:
    inline static bool runtime_err = false;
};