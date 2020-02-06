#include <cspec.hpp>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>

Bench(something)
{
  const auto reps = 1000000;
  const auto array_size = 16384;

  Do(reps)
  {
    char* arr = (char*)malloc(sizeof(char) * array_size);
    memset(arr, 0, sizeof(char) * array_size);
    free(arr);
  }

  auto ctime = Timer.elapsed<cspec::Microsecond>() / reps;

  Do(reps)
  {
    char* arr = new char[array_size];
    std::fill(arr, arr + array_size, 0);
    delete[] arr;
  }

  auto cpptime = Timer.elapsed<cspec::Microsecond>() / reps;

  std::cout << "ctime: " << ctime << '\n';
  std::cout << "cpptime: " << cpptime << '\n';
}

Bench(another)
{
  const auto reps = 100000;
  const auto array_size = 16384;

  {
    char src[array_size];
    char dst[array_size];

    Do(reps)
    {
      memcpy(dst, src, sizeof(src));
    }
  }

  auto ctime = Timer.elapsed<cspec::Nanosecond>() / reps;

  {
    std::array<char, array_size> src;
    std::array<char, array_size> dst;

    Do(reps)
    {
      std::copy(src.begin(), src.end(), dst.begin());
    }
  }

  auto cpptime = Timer.elapsed<cspec::Nanosecond>() / reps;

  std::cout << "ctime: " << ctime << '\n';
  std::cout << "cpptime: " << cpptime << '\n';
}

