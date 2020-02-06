#pragma once

#include <memory>
#include <deque>

#include "clock.hpp"

#define Bench(benchmark_name)                                                \
    class _benchmark_##benchmark_name##_ : public cspec::Benchmark           \
    {                                                                        \
       public:                                                               \
        _benchmark_##benchmark_name##_() : cspec::Benchmark(#benchmark_name) \
        {}                                                                   \
        void body() override;                                                \
    };                                                                       \
    _benchmark_##benchmark_name##_ _var_##benchmark_name##_;                 \
    void _benchmark_##benchmark_name##_::body()

#define Do(times)  \
    Timer.reset(); \
    for (unsigned long i = 0u; i < times; i++)

extern cspec::Clock Timer;

namespace cspec
{
    class Benchmark
    {
       public:
        Benchmark(const char* name);

        static void Run();

        const char* Name;

        virtual void body() = 0;

       private:
		static std::unique_ptr<std::deque<Benchmark*>> sBenchmarks;
    };
}  // namespace cspec
