#pragma once

namespace cspec {
  typedef std::function<void(void)> TestFunc;

  class Test {
    public:
      Test(const char* name, TestFunc test);

      void operator()();

    private:
      const char* mName;
      TestFunc mTest;
  };
}

