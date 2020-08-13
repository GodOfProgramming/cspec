#include <algorithm>
#include <cstring>
#include "cspec/cspec.hpp"
#include "cspec/internal/misc.hpp"

namespace
{
  bool gEvaluationInitalized = false;
}

namespace cspec
{
  std::unique_ptr<std::deque<Evaluation*>> Evaluation::Tests;

  Evaluation::Evaluation(char const* test_name): Name(test_name)
  {
    if (!gEvaluationInitalized) {
      Tests = std::make_unique<std::deque<Evaluation*>>();
      gEvaluationInitalized = true;
    }
    Tests->push_back(this);
  }

  void Evaluation::Run()
  {
    std::sort(Tests->begin(), Tests->end(), [](Evaluation* a, Evaluation* b) -> bool {
      return strcmp(a->Name, b->Name) < 0;
    });

    cspec::print("Running ", Tests->size(), " evaluations\n");
    for (auto& test : *Tests) {
      cspec::print('\n', "Evaluating: ", "\x1b[35m", test->Name);
      std::cout << std::endl;
      test->body();
    }
  }
}  // namespace cspec
