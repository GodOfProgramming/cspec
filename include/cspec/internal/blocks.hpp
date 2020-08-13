#pragma once
#include <functional>
#include <vector>
#include <deque>

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

  inline TestBlock::TestBlock(const char* desc, TestFunc test): Desc(desc), Test(test) {}

  inline void TestBlock::run()
  {
    Test();
  }

  class DescribeBlock: public TestBlock
  {
   public:
    DescribeBlock(const char* name, TestFunc test);
  };

  inline DescribeBlock::DescribeBlock(const char* name, TestFunc test): TestBlock(name, test) {}

  class ContextBlock: public TestBlock
  {
   public:
    ContextBlock(const char* name, TestFunc test);
  };

  inline ContextBlock::ContextBlock(const char* name, TestFunc test): TestBlock(name, test) {}

  class ItBlock: public TestBlock
  {
   public:
    ItBlock(const char* name, TestFunc test);

    void run() override;

    std::deque<TestBlock*> PrevTests;
  };

  inline ItBlock::ItBlock(const char* name, TestFunc test): TestBlock(name, test) {}

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