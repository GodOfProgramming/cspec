#pragma once
#include <queue>
#include <functional>
#include <memory>
#include "expectation.hpp"
#include "test_block.hpp"

/* Define a variable to hold the value of the self executing lambda */
#define BeginSpec(test_name) int var##test_name = [] {

/* Return 0 and execute the lambda */
#define EndSpec return 0; }();

#define Describe(desc, func) cspec::_Describe_(desc, func)
#define Context(context, func) cspec::_Context_(context, func)
#define It(test, func) cspec::_It_(test, func, __FILE__, __LINE__)
#define BeforeEach(func) 

namespace cspec {
  typedef std::shared_ptr<TestBlock> BlockPtr;

  void _Describe_(const char* desc, TestFunc func);
  void _Context_(const char* context, TestFunc func);
  void _It_(const char* test, TestFunc func, const char* file, int line);
  void _BeforeEach_(TestFunc func);

  class SpecRunner {
    public:
      static void RunTests();
  };
}

