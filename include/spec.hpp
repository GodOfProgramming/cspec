#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <deque>
#include "expectation.hpp"
#include "exceptions.hpp"
#include "blocks.hpp"
#include "custom_vector.hpp"

/* Define a variable to hold the value of the self executing lambda */
#define BeginSpec(test_name) int var##test_name = [] { \
    cspec::gCurrentTest = std::make_shared<cspec::Test>(); \
    cspec::gCurrentTest->first = #test_name
/* Return 0 and execute the lambda */
#define EndSpec()                                 \
    cspec::gTests.push_back(cspec::gCurrentTest); \
    return 0;                                     \
    }                                             \
    ()

/* Has to use __VA_ARGS__ here because of how preprocessor parsing works,
 * otherwise anything in the capture list of the function (ex: [foo, bar] {})
 * will be split into multiple args for the func.
 *
 * So what happens using the above as the example is this:
 * If "It" is defined as: It(test, func)
 * then It("something", [foo, bar] {}) is interpreted as three args
 * instead of "test" and the lambda. "[foo" is one and "bar] {}" is the other
 */

#define Describe cspec::_Describe_
#define Context cspec::_Context_
#define It cspec::_It_
#define BeforeEach cspec::_BeforeEach_
#define AfterEach cspec::_AfterEach_

#define Expect cspec::_Expect_

extern std::vector<const char*> ARGV;

namespace cspec
{
    using Description = std::pair<const char*, TestFunc>;
    using DescriptionQueue = std::deque<Description>;
    using Test = std::pair<const char*, DescriptionQueue>;
    using TestPtr = std::shared_ptr<Test>;
    using TestQueue = std::deque<TestPtr>;

    extern TestQueue gTests;
    extern TestPtr gCurrentTest;
    typedef std::shared_ptr<TestBlock> BlockPtr;

    void _Describe_(const char* desc, TestFunc func);
    void _Context_(const char* context, TestFunc func);
    void _It_(const char* test, TestFunc func);
    void _BeforeEach_(TestFunc func);
    void _AfterEach_(TestFunc func);

    template <typename T>
    Expectation<T> _Expect_(T expectation)
    {
        if (!gInItBlock) {
            throw InvalidExpectationException();
        }
        return Expectation<T>(expectation);
    }

    class SpecRunner
    {
       public:
        static void RunTests();
    };
}  // namespace cspec
