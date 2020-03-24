#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "evaluation.hpp"
#include "expectation.hpp"
#include "exceptions.hpp"
#include "blocks.hpp"
#include "benchmark.hpp"

#define Describe cspec::_Describe_
#define Context cspec::_Context_
#define It cspec::_It_
#define BeforeEach cspec::_BeforeEach_
#define AfterEach cspec::_AfterEach_

#define Expect(expectation) cspec::_Expect_(expectation, __FILE__, __LINE__)

extern std::unordered_map<std::string, std::string> ENV;
extern std::vector<std::string> ARGV;

namespace cspec
{
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
