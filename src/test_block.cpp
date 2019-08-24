#include "test_block.hpp"

namespace cspec {
TestBlock::TestBlock(const char* desc, TestFunc test)
    : Desc(desc), Test(test) {}

void TestBlock::run() { Test(); }
}
