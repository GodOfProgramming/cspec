#pragma once
#include "test.hpp"

namespace cspec : public Test {
  class it {
    it(const char* name, std::function<void(void)> test);
  };
}

