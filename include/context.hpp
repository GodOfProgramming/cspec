#pragma once
#include "test_block.hpp"

namespace cspec {
  class Context : public TestBlock {
    public:
      Context(const char* name, TestFunc test);
  };
}
