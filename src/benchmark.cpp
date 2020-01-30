#include "benchmark.hpp"

#include <iostream>

cspec::Clock Timer;

namespace cspec
{
    std::deque<Benchmark*> Benchmark::sBenchmarks;

    Benchmark::Benchmark(const char* name) : Name(name)
    {
        sBenchmarks.push_back(this);
    }

    void Benchmark::Run()
    {
        std::cout << "Running " << sBenchmarks.size() << " benchmarks\n";
        for (auto benchmark : sBenchmarks) {
            std::cout << "\n\n" << benchmark->Name << "\n\n";
            benchmark->body();
        }
    }
}  // namespace cspec

