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
    class _test_##test_name##_ : public cspec::Evaluation                        \
    {                                                                           \
       public:                                                                  \
        _test_##test_name##_();                                                 \
        void body() override;                                                   \
    };                                                                          \
    _test_##test_name##_ _var_##test_name##_;                                   \
    _test_##test_name##_::_test_##test_name##_() : cspec::Evaluation(#test_name) \
    {}                                                                          \
    void _test_##test_name##_::body()

#define Describe cspec::_Describe_
#define Context cspec::_Context_
#define It cspec::_It_
#define BeforeEach cspec::_BeforeEach_
#define AfterEach cspec::_AfterEach_

#define Expect(expectation) cspec::_Expect_(expectation, __FILE__, __LINE__)

extern std::unordered_map<std::string, std::string> ENV;
extern std::vector<const char*> ARGV;

namespace cspec
{
    class Evaluation
    {
       public:
        Evaluation(char const* test_name);

	static void Run();

        virtual void body() = 0;

        char const* Name;

       private:
        static std::deque<Evaluation*> sTests;
    };

    extern unsigned int gSpecCount;
    extern unsigned int gFailures;

    void _Describe_(const char* desc, TestFunc func);
    void _Context_(const char* context, TestFunc func);
    void _It_(const char* test, TestFunc func);
    void _BeforeEach_(TestFunc func);
    void _AfterEach_(TestFunc func);

    template <typename T>
    Expectation<T> _Expect_(T expectation, const char* file, int line)
    {
        if (!gInItBlock) {
            throw InvalidExpectationException(file, line);
        }
        return Expectation<T>(expectation, file, line);
    }
}  // namespace cspec
