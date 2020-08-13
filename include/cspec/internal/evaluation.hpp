#pragma once

#include <memory>
#include <deque>

#define Eval(test_name)                                                          \
  class _test_##test_name##_: public cspec::Evaluation                           \
  {                                                                              \
   public:                                                                       \
    _test_##test_name##_();                                                      \
    void body() override;                                                        \
  };                                                                             \
  _test_##test_name##_ _var_##test_name##_;                                      \
  _test_##test_name##_::_test_##test_name##_(): cspec::Evaluation(#test_name) {} \
  void _test_##test_name##_::body()

namespace cspec
{
  class Evaluation
  {
   public:
    Evaluation(char const* test_name);

    static void Run();

    virtual void body() = 0;

    char const* Name;

   private:
    static std::unique_ptr<std::deque<Evaluation*>> Tests;
  };
}  // namespace cspec
