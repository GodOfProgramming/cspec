#pragma once
#include "test_block.hpp"
#include <vector>

namespace cspec {
class ContextBlock : public TestBlock
{
public:
  ContextBlock(const char* name, TestFunc test);
};
}
