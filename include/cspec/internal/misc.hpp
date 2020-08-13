#pragma once

#include <iostream>
#include <sstream>

namespace cspec
{
    extern std::stringstream gFailureMessages;

    template <typename... Args>
    inline void print(Args&&... args)
    {
        ((std::cout << std::forward<Args>(args)), ...) << "\x1b[m";
    }

    template <typename... Args>
    inline void capture(Args&&... args)
    {
        ((gFailureMessages << std::forward<Args>(args)), ...) << "\x1b[m";
    }

    inline std::string captures()
    {
        auto capts = gFailureMessages.str();
        gFailureMessages.str(std::string());
        return capts;
    }
}  // namespace cspec
