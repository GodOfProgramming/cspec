#include <exception>
#include <sstream>
#include <algorithm>
#include "cspec.hpp"
#include "blocks.hpp"
#include "exceptions.hpp"
#include "expectation.hpp"

#define TAB_STR "  "

sys::Env ENV;
std::vector<const char*> ARGV;
dash::Console console;

namespace cspec
{
    using TestQueue = std::deque<CspecTest*>;

    bool gInItBlock = false;
    bool gItFailed = false;

    unsigned int gSpecCount = 0;
    unsigned int gFailures = 0;

    TestQueue gTests;

    CspecTest::CspecTest(char const* test_name) : TestName(test_name)
    {
        gTests.push_back(this);
    }
}  // namespace cspec

namespace
{
    std::deque<cspec::TestBlock*> gRunningTests;
    cspec::TestBlock* gRunningTest = nullptr;

    void printCurrentTestStack()
    {
        int tabcount = 1;
        for (const auto& test : gRunningTests) {
            for (int i = 0; i < tabcount; i++) {
                console.write(TAB_STR);
            }
            console.write(test->Desc, '\n');
            tabcount++;
        }
    }
}  // namespace

namespace cspec
{
    void RunTest(TestBlock& test)
    {
        try {
            test.run();
        } catch (InvalidExpectationException e) {
            console.write("Expectations can only be executed within it blocks", '\n');
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

        if (gItFailed) {
            gFailures++;
            gItFailed = false;
            printCurrentTestStack();
        } else {
            console.write(console.setOpt<dash::Mod::FG_Green>(), "\u2022");
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
}  // namespace cspec

int main(int argc, char* argv[])
{
    ARGV.resize(argc);
    for (int i = 0; i < argc; i++) {
        ARGV[i] = argv[i];
    }

    std::sort(cspec::gTests.begin(), cspec::gTests.end(), [](cspec::CspecTest* a, cspec::CspecTest* b) -> bool {
        return strcmp(a->TestName, b->TestName) < 0;
    });

    for (auto& test : cspec::gTests) {
        console.write('\n', "Executing: ", console.setOpt<dash::Mod::FG_Magenta>(), test->TestName, '\n');
        test->body();
    }

    console.write("\n\n",
        "Executed ",
        cspec::gSpecCount,
        " test",
        cspec::gSpecCount == 1 ? "" : "s",
        " with ",
        cspec::gFailures,
        " failure",
        cspec::gFailures == 1 ? "" : "s",
        '\n');
    return !cspec::gFailures ? 0 : 1;
}
