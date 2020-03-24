#include <cspec/cspec.hpp>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <deque>

[[gnu::always_inline]] inline void iterate(std::unordered_map<int, int>& map)
{
  asm("");
  for (const auto& pair : map) {
    (void)pair;
    // do nothing
  }
}

[[gnu::always_inline]] inline void iterate(std::deque<int>& deque)
{
  asm("");
  for (const auto& num : deque) {
    (void)num;
    // do nothing
  }
}

[[gnu::always_inline]] inline void iterate(std::array<int, 1024>& arr)
{
  asm("");
  for (const auto& num : arr) {
    (void)num;
  }
}

Bench(unordered_map_vs_array_iteration)
{
  const auto reps = 10000000;
  const auto size = 1024;

  std::unordered_map<int, int> map;
  map.reserve(size);
  std::array<int, size> arr;
  std::deque<int> deque;

  for (int i = 0; i < size; i++) {
    map[i] = i;
    arr[i] = i;
    deque.push_back(i);
  }

  {
    Do(reps)
    {
      iterate(map);
    }

    const auto elapsed = Timer.elapsed<cspec::Nanosecond>() / reps;
    std::cout << "Map: " << elapsed << '\n';
  }

  {
    Do(reps)
    {
      iterate(deque);
    }

    const auto elapsed = Timer.elapsed<cspec::Nanosecond>() / reps;
    std::cout << "Deque: " << elapsed << '\n';
  }

  {
    Do(reps)
    {
      iterate(arr);
    }

    const auto elapsed = Timer.elapsed<cspec::Nanosecond>() / reps;
    std::cout << "Arr: " << elapsed << '\n';
  }
}

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

