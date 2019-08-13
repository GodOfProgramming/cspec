#include "Spec.hpp"
#include "Expectation.hpp"
#include "CustomVector.hpp"
#include "Exceptions.hpp"

static CustomVector<const char*> gTestDescStack;

std::queue<std::function<void(void)>> Spec::mTests;
bool gInItBlock = false;
bool gItFailed = false;
static bool gAllPassed = true;

void RunFunc(std::function<void(void)> func) {
  try {
    func();
  } catch (InvalidExpectationException e) {
    std::cout << "Expectations can only be executed within it blocks" << std::endl;
    gAllPassed = false;
  }
}

void _Describe_(const char* desc, std::function<void(void)> func) {
  gTestDescStack.clear();
  Context(desc, func);
}

void _Context_(const char* context, std::function<void(void)> func) {
  gTestDescStack.push(context);
  RunFunc(func);
}

void _It_(const char* test, std::function<void(void)> func, const char* file, int line) {
  gInItBlock = true;
  gTestDescStack.push(test);
  RunFunc(func);
  gInItBlock = false;

  if (gItFailed) {
    gItFailed = false;
    gAllPassed = false;
    int tabcount = 1;
    std::cout << "Failure at: " << file << '(' << line << ')' << '\n';
    for (const auto& desc : gTestDescStack) {
      for (int i = 0; i < tabcount; i++) {
	std::cout << '\t';
      }
      std::cout << desc << '\n';
      tabcount++;
    }
  }
}

void Spec::RunTests() {
  while(!mTests.empty()) {
    auto test = mTests.front();
    test();
    mTests.pop();
  }
}

int main() {
  Spec::RunTests();
  return gAllPassed ? 0 : 1;
}
