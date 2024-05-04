#pragma once

template<typename Func>
struct ScopedGuardImpl
{
    Func&& fn;
    ~ScopedGuardImpl() 
    {
        std::forward<Func>(fn)();
    }
};

#define CONCAT2(LINE) guard__##LINE
#define CONCAT(LINE) CONCAT2(LINE)
#define ScopedGuard(fn) const auto CONCAT(__LINE__) = ScopedGuardImpl{ fn };