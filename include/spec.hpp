#pragma once
#include <functional>
#include <memory>
#include <queue>
#include "expectation.hpp"
#include "exceptions.hpp"
#include "test_block.hpp"

/* Define a variable to hold the value of the self executing lambda */
#define BeginSpec(test_name) int var##test_name = [] { \
    cspec::console.write('\n', "Executing: ", cspec::console.setOpt<cspec::Console::Mod::FG_Magenta>(), #test_name, '\n')
/* Return 0 and execute the lambda */
#define EndSpec() \
  return 0;       \
  }               \
  ()

/* Has to use __VA_ARGS__ here because of how preprocessor parsing works,
 * otherwise anything in the capture list of the function (ex: [foo, bar] {})
 * will be split into multiple args for the func.
 *
 * So what happens using the above as the example is this:
 * If "It" is defined as: It(test, func)
 * then It("something", [foo, bar] {}) is interpreted as three args
 * instead of "test" and the lambda. "[foo" is one and "bar] {}" is the other
 */

#define Describe(desc, ...) cspec::_Describe_(desc, __VA_ARGS__)
#define Context(context, ...) cspec::_Context_(context, __VA_ARGS__) 
#define It(test, ...) cspec::_It_(test, __VA_ARGS__, __FILE__, __LINE__)
#define BeforeEach(...) cspec::_BeforeEach_(__VA_ARGS__)
#define AfterEach(...) cspec::_AfterEach_(__VA_ARGS__)

#define Expect(expectation) cspec::_Expect_(expectation)

namespace cspec {
  typedef std::shared_ptr<TestBlock> BlockPtr;

  void _Describe_(const char* desc, TestFunc func);
  void _Context_(const char* context, TestFunc func);
  void _It_(const char* test, TestFunc func, const char* file, int line);
  void _BeforeEach_(TestFunc func);
  void _AfterEach_(TestFunc func);
  void printCurrentTestStack();

  template <typename T>
  Expectation<T> _Expect_(T expectation) {
    if (!gInItBlock) {
      throw InvalidExpectationException();
    }
    return Expectation<T>(expectation);
  }

  class SpecRunner {
   public:
    static void RunTests();
  };
}  // namespace cspec
