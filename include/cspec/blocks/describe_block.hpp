#pragma once
#include <vector>
#include "test_block.hpp"

namespace cspec
{
    class DescribeBlock : public TestBlock
    {
       public:
        DescribeBlock(const char* name, TestFunc test);
    };

    inline DescribeBlock::DescribeBlock(const char* name, TestFunc test) : TestBlock(name, test)
    {}
}  // namespace cspec
