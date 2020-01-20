#pragma once
#include <vector>
#include "test_block.hpp"

namespace cspec {
  class DescribeBlock : public TestBlock {
   public:
    inline DescribeBlock(const char* name, TestFunc test) : TestBlock(name, test) {
    }
  };  // namespace cspec
}  // namespace cspec

