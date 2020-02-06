#include "benchmark.hpp"

#include <iostream>

cspec::Clock Timer;

namespace
{
	bool gBenchmarkInitalized = false;
}

namespace cspec
{
	std::unique_ptr<std::deque<Benchmark*>> Benchmark::sBenchmarks;

	Benchmark::Benchmark(const char* name): Name(name)
	{
		if (!gBenchmarkInitalized) {
			sBenchmarks = std::make_unique<std::deque<Benchmark*>>();
			gBenchmarkInitalized = true;
		}

		sBenchmarks->push_back(this);
	}

	void Benchmark::Run()
	{
		std::cout << "Running " << sBenchmarks->size() << " benchmarks\n";
		for (auto benchmark : *sBenchmarks) {
			std::cout << "\n\n" << benchmark->Name << "\n\n";
			benchmark->body();
		}
	}
}  // namespace cspec

