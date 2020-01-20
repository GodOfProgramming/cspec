#pragma once
#include <vector>
#include "test_block.hpp"

namespace cspec {
  class ContextBlock : public TestBlock {
   public:
    inline ContextBlock(const char* name, TestFunc test) : TestBlock(name, test) {
    }
  };  // namespace cspec
}  // namespace cspec

