#pragma once
#include <vector>
#include "test_block.hpp"
#include "context_block.hpp"
#include "it_block.hpp"

namespace cspec {
  class DescribeBlock : public TestBlock {
    public:
      DescribeBlock(const char* name, TestFunc test);

    private:
      std::vector<ContextBlock> mContexts;
      std::vector<ItBlock> mItBlocks;
  };
}
