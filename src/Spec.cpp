#include "Spec.hpp"
#include "Expectation.hpp"
#include "CustomVector.hpp"
#include "Exceptions.hpp"

static CustomVector<const char*> gTestDescStack;

std::queue<std::function<void(void)>> Spec::mTests;

bool gInItBlock = false;
static bool gAllPassed = true;

void RunFunc(std::function<void(void)> func) {
  try {
    func();
  } catch (InvalidExpectationException e) {
    std::cout << "Expectations can only be executed within it blocks" << std::endl;
    gAllPassed = false;
  } catch (SpecFailureException e) {
    gAllPassed = false;
    int tabcount = 1;
    for (const auto& desc : gTestDescStack) {
      for (int i = 0; i < tabcount; i++) {
        std::cout << '\t';
      }
      std::cout << desc << std::endl;
      tabcount++;
    }
  }
}

void Describe(const char* desc, std::function<void(void)> func) {
  gTestDescStack.clear();
  Context(desc, func);
}

void Context(const char* context, std::function<void(void)> func) {
  gTestDescStack.push(context);
  RunFunc(func);
}

void It(const char* test, std::function<void(void)> func) {
  gInItBlock = true;
  gTestDescStack.push(test);
  RunFunc(func); // don't need this wrapper, but for consistency
  gInItBlock = false;
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
