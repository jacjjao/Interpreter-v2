#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include "Expr.hpp"

class Environment
{
public:
    bool declare(const std::string& name, const Expr::r_type& val);

    std::optional<Expr::r_type> get(const std::string& name) const;

    bool set(const std::string& name, const Expr::r_type& val);

private:
    std::unordered_map<std::string, Expr::r_type> var_;
};