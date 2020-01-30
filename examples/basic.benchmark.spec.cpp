#include <cspec.hpp>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>

Bench(something)
{
    Do(100)
    {
        char* arr = (char*)malloc(sizeof(char) * 128);
        memset(arr, 0, sizeof(char) * 128);
        free(arr);
    }

    auto ctime = Timer.elapsed<cspec::Microsecond>() / 100;

    Do(100)
    {
        char* arr = new char[128];
        std::fill(arr, arr + 128, 0);
        delete[] arr;
    }

    auto cpptime = Timer.elapsed<cspec::Microsecond>() / 100;

    std::cout << "ctime: " << ctime << '\n';
    std::cout << "cpptime: " << cpptime << '\n';
}
