#include "pch.hpp"
#include "Lox.hpp"

void Lox::report(int line, const char* err_msg)
{
    std::cerr << std::format("[line {}] error: {}\n", line, err_msg);
}

void Lox::error(const int line, const char* err_msg)
{
    report(line, err_msg);
}

void Lox::runtimeError(int line, const char* err_msg)
{
    std::cerr << std::format("[line {}] Runtime error: {}\n", line, err_msg);
    runtime_err = true;
}

bool Lox::hadRuntimeErr()
{
    bool v = runtime_err;
    runtime_err = false;
    return v;
}

void Lox::printInterpretResult(const Expr::r_type& result)
{
    if (std::holds_alternative<std::monostate>(result))
    {
        std::cout << "null\n";
        return;
    }
    else if (std::holds_alternative<double>(result))
    {
        std::cout << std::format("{}\n", std::get<double>(result));
        return;
    }
    else if (std::holds_alternative<std::string>(result))
    {
        std::cout << std::format("\'{}\'\n", std::get<std::string>(result));
        return;
    }
    else if (std::holds_alternative<bool>(result))
    {
        bool b = std::get<bool>(result);
        if (b)
            std::cout << "true\n";
        else
            std::cout << "false\n";
        return;
    }

    throw std::runtime_error("Fatal internal error, cannot print result.");
}
