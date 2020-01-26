#pragma once
#include <deque>
#include "test_block.hpp"

namespace cspec
{
    class ItBlock : public TestBlock
    {
       public:
        ItBlock(const char* name, TestFunc test);

        void run() override;

        std::deque<TestBlock*> PrevTests;
    };

    inline ItBlock::ItBlock(const char* name, TestFunc test) : TestBlock(name, test)
    {}

    inline void ItBlock::run()
    {
        for (const auto& test : PrevTests) {
            if (test->beforeEach) {
                test->beforeEach();
            }
        }

        TestBlock::run();

        for (const auto& test : PrevTests) {
            if (test->afterEach) {
                test->afterEach();
            }
        }
    }
}  // namespace cspec
