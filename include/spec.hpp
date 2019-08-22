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

#define Describe(desc, ...) cspec::_Describe_(desc, __VA_ARGS__)
#define Context(context, ...) cspec::_Context_(context, __VA_ARGS__)
#define It(test, ...) cspec::_It_(test, __VA_ARGS__, __FILE__, __LINE__)
#define BeforeEach(...) cspec::_BeforeEach_(__VA_ARGS__)
#define AfterEach(...) cspec::_AfterEach_(__VA_ARGS__)

namespace cspec {
  typedef std::shared_ptr<TestBlock> BlockPtr;

  void _Describe_(const char* desc, TestFunc func);
  void _Context_(const char* context, TestFunc func);
  void _It_(const char* test, TestFunc func, const char* file, int line);
  void _BeforeEach_(TestFunc func);
  void _AfterEach_(TestFunc func);
  void printCurrentTestStack();

  class SpecRunner {
    public:
      static void RunTests();
  };
}

