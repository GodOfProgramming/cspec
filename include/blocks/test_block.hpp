#pragma once
#include <functional>
#include <vector>

namespace cspec
{
    using TestFunc = std::function<void(void)>;

    class TestBlock
    {
       public:
        TestBlock(const char* desc, TestFunc test);
        virtual ~TestBlock() = default;

        virtual void run();

        TestFunc beforeEach;
        TestFunc afterEach;

        const char* const Desc;
        const TestFunc Test;
    };

    inline TestBlock::TestBlock(const char* desc, TestFunc test) : Desc(desc), Test(test)
    {}

    inline void TestBlock::run()
    {
        Test();
    }
}  // namespace cspec
