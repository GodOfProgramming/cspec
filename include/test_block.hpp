#pragma once
#include <functional>
#include <vector>
#include "custom_vector.hpp"

namespace cspec {
  typedef std::function<void(void)> TestFunc;

  class TestBlock {
    public:
      TestBlock(const char* name, TestFunc test);
      virtual ~TestBlock() = default;

      virtual void run();

      TestFunc beforeEach;

    private:
      const char* mName;
      TestFunc mTest;
  };
}

