#include "test.hpp"

namespace cspec {
  Test::Test(const char* name, TestFunc test) : mName(name), mTest(test) { }

  void Test::operator()() {
    mTest();
  }
}

