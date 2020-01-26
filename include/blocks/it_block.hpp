#pragma once
#include <deque>
#include "test_block.hpp"

namespace cspec {
  class ItBlock : public TestBlock {
   public:
    inline ItBlock(const char* name, TestFunc test) : TestBlock(name, test) {
    }

    inline void run() override {
      for (const auto& test : PrevTests) {
        if (test->beforeEach) {
          test->beforeEach();
        }
      }

      TestBlock::run();

      for (const auto& test : PrevTests) {
        if (test->afterEach) {
          test->afterEach();
        }
      }
    }

    std::deque<TestBlock*> PrevTests;
  };
}  // namespace cspec
