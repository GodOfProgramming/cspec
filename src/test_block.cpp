#include "test_block.hpp"

namespace cspec {
  TestBlock::TestBlock(const char* name, TestFunc test) : mName(name), mTest(test) { }

  void TestBlock::run() {
    mTest();
  }
}

