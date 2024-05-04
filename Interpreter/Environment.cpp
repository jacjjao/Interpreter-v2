#include "Environment.hpp"

bool Environment::declare(const std::string& name, const Expr::r_type& val)
{
    if (var_.contains(name)) {
        return false;
    }
    var_[name] = val;
    return true;
}

std::optional<Expr::r_type> Environment::get(const std::string& name) const
{
    const auto it = var_.find(name);
    if (it == var_.end()) {
        return std::nullopt;
    }
    return it->second;
}

bool Environment::set(const std::string& name, const Expr::r_type& val)
{
    const auto it = var_.find(name);
    if (it == var_.end()) {
        return false;
    }
    it->second = val;
    return true;
}
