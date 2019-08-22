#pragma once
#include <vector>
#include "test_block.hpp"

namespace cspec {
  class ContextBlock : public TestBlock {
    public:
      ContextBlock(const char* name, TestFunc test);
  };
}
