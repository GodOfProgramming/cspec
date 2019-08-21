#pragma once
#include <queue>
#include <functional>
#include "expectation.hpp"

/* Define a variable to hold the value of the self executing lambda */
#define BeginSpec(test_name) int var##test_name = [] {

/* Return 0 and execute the lambda */
#define EndSpec return 0; }();

#define Describe(desc, func) cspec::_Describe_(desc, func)
#define Context(context, func) cspec::_Context_(context, func)
#define It(test, func) cspec::_It_(test, func, __FILE__, __LINE__)

namespace cspec {
  void _Describe_(const char* desc, std::function<void(void)> func);
  void _Context_(const char* context, std::function<void(void)> func);
  void _It_(const char* test, std::function<void(void)> func, const char* file, int line);

  class SpecRunner {
    public:
      static void RunTests();

    private:
      static std::queue<std::function<void(void)>> mTests;
  };
}

