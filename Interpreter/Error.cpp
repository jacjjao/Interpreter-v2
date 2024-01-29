#include "Error.hpp"
#include <iostream>
#include <format>

void Lox::report(int line, const char* err_msg)
{
    std::cerr << std::format("[line {}] error: {}\n", line, err_msg);
}

void Lox::error(const int line, const char* err_msg)
{
    report(line, err_msg);
}
