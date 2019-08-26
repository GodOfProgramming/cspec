#include "describe_block.hpp"

namespace cspec {
  DescribeBlock::DescribeBlock(const char* name, TestFunc test) : TestBlock(name, test) {
  }
}  // namespace cspec
