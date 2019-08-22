#pragma once
#include <functional>
#include <vector>
#include "custom_vector.hpp"

namespace cspec {
  typedef std::function<void(void)> TestFunc;

  class TestBlock {
    public:
      TestBlock(const char* desc, TestFunc test);
      virtual ~TestBlock() = default;

      virtual void run();

      TestFunc beforeEach;

      const char* const Desc;
      const TestFunc Test;
  };
}

