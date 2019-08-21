#pragma once
#include "test_block.hpp"

namespace cspec  {
  class ItBlock : public TestBlock {
    public:
      ItBlock(const char* name, TestFunc test);
  };
}

