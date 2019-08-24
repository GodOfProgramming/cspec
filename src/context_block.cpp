#include "context_block.hpp"

namespace cspec {
ContextBlock::ContextBlock(const char* name, TestFunc test)
    : TestBlock(name, test) {}
}
