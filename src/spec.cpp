#include <console.hpp>
#include <exception>
#include <sstream>
#include "spec.hpp"
#include "blocks.hpp"
#include "exceptions.hpp"
#include "expectation.hpp"
#include "custom_vector.hpp"

#define TAB_STR "  "

dash::Console console;
std::vector<const char*> ARGV;

namespace cspec
{
    bool gInItBlock = false;
    bool gItFailed = false;
    unsigned int gSpecCount = 0;
    unsigned int gFailures = 0;
    TestQueue gTests;
    TestPtr gCurrentTest;
}  // namespace cspec

namespace
{
    cspec::CustomVector<cspec::TestBlock*> gRunningTests;
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
        gCurrentTest->second.push_back({ desc, func });
    }

    void _Context_(const char* context, TestFunc func)
    {
        auto prev_test = gRunningTest;
        ContextBlock cb(context, func);
        gRunningTest = &cb;
        gRunningTests.push(gRunningTest);
        RunTest(cb);
        gRunningTests.pop();
        gRunningTest = prev_test;
    }

    void _It_(const char* test, TestFunc func)
    {
        auto prev_test = gRunningTest;
        ItBlock ib(test, func);
        ib.PrevTests = gRunningTests;
        gRunningTest = &ib;
        gRunningTests.push(gRunningTest);

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

        gRunningTests.pop();
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

    for (auto& test : cspec::gTests) {
        console.write('\n', "Executing: ", console.setOpt<dash::Mod::FG_Magenta>(), test->first, '\n');
        for (auto& desc : test->second) {
            auto prev_test = gRunningTest;
            cspec::DescribeBlock db(desc.first, desc.second);
            gRunningTest = &db;
            gRunningTests.push(gRunningTest);
            RunTest(db);
            gRunningTests.pop();
            gRunningTest = prev_test;
        }
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
