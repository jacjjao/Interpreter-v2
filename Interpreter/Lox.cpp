#include "Lox.hpp"
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

void Lox::printInterpretResult(const std::optional<Expr::r_type>& result)
{
    if (!result)
        return;

    if (std::holds_alternative<double>(*result))
    {
        std::cout << std::format("{}\n", std::get<double>(*result));
        return;
    }
    if (std::holds_alternative<std::string>(*result))
    {
        std::cout << std::format("\'{}\'\n", std::get<std::string>(*result));
        return;
    }
    if (std::holds_alternative<bool>(*result))
    {
        bool b = std::get<bool>(*result);
        if (b)
            std::cout << "true\n";
        else
            std::cout << "false\n";
        return;
    }

    throw std::runtime_error("Fatal internal error, cannot print result.");
}
