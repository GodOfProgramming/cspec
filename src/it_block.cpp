#include "it_block.hpp"
#include "console.hpp"

namespace cspec {
  ItBlock::ItBlock(const char* name, TestFunc test) : TestBlock(name, test) { }

  void ItBlock::run() {
    for(const auto& test : PrevTests) {
      if (test->beforeEach) {
	test->beforeEach();
      }
    }

    TestBlock::run();

    for(const auto& test : PrevTests) {
      if (test->afterEach) {
	test->afterEach();
      }
    }
  }
}

