#pragma once
#include <vector>
#include "test_block.hpp"
#include "it_block.hpp"

namespace cspec {
  class ContextBlock : public TestBlock {
    public:
      ContextBlock(const char* name, TestFunc test);

    private:
      std::vector<ItBlock> mItBlocks;
  };
}
