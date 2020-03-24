#include "cspec/evaluation.hpp"

#include <algorithm>
#include <cstring>

#include "cspec/misc.hpp"

namespace
{
	bool gEvaluationInitalized = false;
}

namespace cspec
{
	std::unique_ptr<std::deque<Evaluation*>> Evaluation::sTests;

	Evaluation::Evaluation(char const* test_name): Name(test_name)
	{
		if (!gEvaluationInitalized) {
			sTests = std::make_unique<std::deque<Evaluation*>>();
			gEvaluationInitalized = true;
		}
		sTests->push_back(this);
	}

	void Evaluation::Run()
	{
		std::sort(sTests->begin(), sTests->end(), [](Evaluation* a, Evaluation* b) -> bool {
			return strcmp(a->Name, b->Name) < 0;
		});

		cspec::print("Running ", sTests->size(), " evaluations\n");
		for (auto& test : *sTests) {
			cspec::print('\n', "Evaluating: ", "\x1b[35m", test->Name);
			std::cout << std::endl;
			test->body();
		}
	}
}  // namespace cspec
