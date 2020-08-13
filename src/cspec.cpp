#include <exception>
#include <sstream>
#include <algorithm>
#include "cspec/cspec.hpp"
#include "cspec/internal/misc.hpp"
#include "cspec/internal/blocks.hpp"
#include "cspec/internal/exceptions.hpp"
#include "cspec/internal/expectation.hpp"
#include "cspec/internal/failable.hpp"

extern char** environ;
std::unordered_map<std::string, std::string> ENV;
std::vector<std::string> ARGV;

namespace
{
  const auto TAB_STR = "  ";
  std::deque<cspec::TestBlock*> gRunningTests;
  cspec::TestBlock* gRunningTest = nullptr;
}  // namespace

namespace cspec
{
  std::stringstream gFailureMessages;

  bool Failable::ItFailed = false;
  bool gInItBlock = false;

  unsigned int gSpecCount = 0;
  unsigned int gFailures = 0;

  void RunTest(TestBlock& test)
  {
    try {
      test.run();
    } catch (InvalidExpectationException e) {
      print('\n', e.File, " (", e.Line, "): ", "Expectations can only be executed within it blocks", '\n');
    }
  }

  void _Describe_(const char* desc, TestFunc func)
  {
    auto prev_test = gRunningTest;
    cspec::DescribeBlock db(desc, func);
    gRunningTest = &db;
    gRunningTests.push_back(gRunningTest);
    RunTest(db);
    gRunningTests.pop_back();
    gRunningTest = prev_test;
  }

  void _Context_(const char* context, TestFunc func)
  {
    auto prev_test = gRunningTest;
    ContextBlock cb(context, func);
    gRunningTest = &cb;
    gRunningTests.push_back(gRunningTest);
    RunTest(cb);
    gRunningTests.pop_back();
    gRunningTest = prev_test;
  }

  void _It_(const char* test, TestFunc func)
  {
    auto prev_test = gRunningTest;
    ItBlock ib(test, func);
    ib.PrevTests = gRunningTests;
    gRunningTest = &ib;
    gRunningTests.push_back(gRunningTest);

    gInItBlock = true;
    RunTest(ib);
    gInItBlock = false;

    gSpecCount++;

    if (Failable::ItFailed) {
      gFailures++;
      Failable::ItFailed = false;
      print("\x1b[31m\u00D7");
    } else {
      print("\x1b[32m\u2022");
    }

    gRunningTests.pop_back();
    gRunningTest = prev_test;
  }

  void _BeforeEach_(TestFunc func)
  {
    if (gRunningTest) {
      gRunningTest->beforeEach = func;
    }
  }

  void _AfterEach_(TestFunc func)
  {
    if (gRunningTest) {
      gRunningTest->afterEach = func;
    }
  }

  void init_env()
  {
    for (int i = 0; environ[i] != nullptr; i++) {
      std::string env = environ[i];

      auto eqpos = env.find_first_of('=');
      auto k = env.substr(0, eqpos);
      auto v = env.substr(eqpos + 1);

      ENV[k] = v;
    }
  }

  void init_argv(int argc, char* argv[])
  {
    ARGV.resize(argc);
    for (int i = 0; i < argc; i++) {
      ARGV[i] = std::string(argv[i]);
    }
  }

  bool check_opt(const char* opt)
  {
    return std::find(ARGV.begin(), ARGV.end(), std::string(opt)) != ARGV.end();
  }

  auto run_tests(int argc, char* argv[]) -> bool
  {
    init_env();
    init_argv(argc, argv);

    // if --no-eval is not present
    if (!check_opt("--no-eval")) {
      cspec::Evaluation::Run();

      cspec::print('\n', cspec::captures());

      cspec::print("\n\n",
       "Evaluated ",
       cspec::gSpecCount,
       " test",
       cspec::gSpecCount == 1 ? "" : "s",
       " with ",
       cspec::gFailures,
       " failure",
       cspec::gFailures == 1 ? "" : "s",
       '\n');
    }

    if (check_opt("--bench")) {
      cspec::Benchmark::Run();
    }

    return cspec::gFailures == 0;
  }
}  // namespace cspec
