#include "cspec/cspec.hpp"

#include <iostream>

cspec::Clock Timer;

namespace
{
	bool gBenchmarkInitalized = false;
}

namespace cspec
{
	std::unique_ptr<std::deque<Benchmark*>> Benchmark::Benchmarks;

	Benchmark::Benchmark(const char* name): Name(name)
	{
		if (!gBenchmarkInitalized) {
			Benchmarks = std::make_unique<std::deque<Benchmark*>>();
			gBenchmarkInitalized = true;
		}

		Benchmarks->push_back(this);
	}

	void Benchmark::Run()
	{
		std::cout << "Running " << Benchmarks->size() << " benchmarks\n";
		for (auto benchmark : *Benchmarks) {
			std::cout << "\n\n" << benchmark->Name << "\n\n";
			benchmark->body();
		}
	}
}  // namespace cspec
