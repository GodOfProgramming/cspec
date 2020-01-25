#pragma once
#include <functional>
#include <vector>
#include "custom_vector.hpp"

namespace cspec {
  using TestFunc = std::function<void(void)>;

  class TestBlock {
   public:
    inline TestBlock(const char* desc, TestFunc test) : Desc(desc), Test(test) {
    }
    virtual ~TestBlock() = default;

    virtual inline void run() {
      Test();
    }

    TestFunc beforeEach;
    TestFunc afterEach;

    const char* const Desc;
    const TestFunc Test;
  };
}  // namespace cspec
