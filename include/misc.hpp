#pragma once
#include <iostream>

namespace cspec
{
    template <typename... Args>
    void print(Args&&... args)
    {
        ((std::cout << std::forward<Args>(args)), ...) << "\x1b[m";
    }
}  // namespace cspec

