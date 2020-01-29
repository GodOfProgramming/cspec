#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <deque>
#include <unordered_map>
#include "expectation.hpp"
#include "exceptions.hpp"
#include "blocks.hpp"

#define Eval(test_name)                                                         \
    class _test_##test_name##_ : public cspec::CspecTest                        \
    {                                                                           \
       public:                                                                  \
        _test_##test_name##_();                                                 \
        void body() override;                                                   \
    };                                                                          \
    _test_##test_name##_ _var_##test_name##_;                                   \
    _test_##test_name##_::_test_##test_name##_() : cspec::CspecTest(#test_name) \
    {}                                                                          \
    void _test_##test_name##_::body()

#define Describe cspec::_Describe_
#define Context cspec::_Context_
#define It cspec::_It_
#define BeforeEach cspec::_BeforeEach_
#define AfterEach cspec::_AfterEach_

#define Expect cspec::_Expect_

extern std::unordered_map<std::string, std::string> ENV;
extern std::vector<const char*> ARGV;

namespace cspec
{
    struct CspecTest
    {
        CspecTest(char const* test_name);
        virtual void body() = 0;
        char const* TestName;
    };

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
}  // namespace cspec
