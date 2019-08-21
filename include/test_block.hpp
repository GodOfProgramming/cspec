#pragma once
#include <functional>

namespace cspec {
  typedef std::function<void(void)> TestFunc;

  class TestBlock {
    public:
      TestBlock(const char* name, TestFunc test);
      virtual ~TestBlock() = default;

      void operator()();

    private:
      const char* mName;
      TestFunc mTest;
  };
}

