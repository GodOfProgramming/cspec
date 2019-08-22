#pragma once
#include "custom_vector.hpp"
#include "test_block.hpp"

namespace cspec  {
  class ItBlock : public TestBlock {
    public:
      ItBlock(const char* name, TestFunc test);

      void run() override;

      CustomVector<TestBlock*> PrevTests;
  };
}

