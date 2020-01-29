#include <exception>
#include <sstream>
#include <algorithm>
#include "cspec.hpp"
#include "misc.hpp"
#include "blocks.hpp"
#include "exceptions.hpp"
#include "expectation.hpp"

#define TAB_STR "  "

extern char** environ;
std::unordered_map<std::string, std::string> ENV;
std::vector<const char*> ARGV;

namespace cspec
{
    std::stringstream gFailureMessages;
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

    void appendCurrentTestStack()
    {
        std::stringstream ss;

        // TODO disabled until described & contexts can be nested properly

        // ss << "\n\n--------------------------------------\n\n\n";
        // int tabcount = 0;
        // for (const auto& test : gRunningTests) {
        //    for (int i = 0; i < tabcount; i++) {
        //	ss << TAB_STR;
        //    }
        //    ss << test->Desc << '\n';
        //    tabcount++;
        //}

        ss << cspec::captures();
        cspec::capture(ss.str());
    }
}  // namespace

namespace cspec
{
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

        if (gItFailed) {
            gFailures++;
            gItFailed = false;
            appendCurrentTestStack();
            print("\x1b[31m", "\u00D7");
        } else {
            print("\x1b[32m", "\u2022");
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
    for (int i = 0; environ[i]; i++) {
        std::string env = environ[i];

        auto eqpos = env.find_first_of('=');
        auto k = env.substr(0, eqpos);
        auto v = env.substr(eqpos + 1);

        ENV[k] = v;
    }

    ARGV.resize(argc);
    for (int i = 0; i < argc; i++) {
        ARGV[i] = argv[i];
    }

    std::sort(cspec::gTests.begin(), cspec::gTests.end(), [](cspec::CspecTest* a, cspec::CspecTest* b) -> bool {
        return strcmp(a->TestName, b->TestName) < 0;
    });

    for (auto& test : cspec::gTests) {
        cspec::print('\n', "Evaluating: ", "\x1b[35m", test->TestName, '\n');
        test->body();
    }

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
    return !cspec::gFailures ? 0 : 1;
}
