#include "console.hpp"
#include "Spec.hpp"
#include "Expectation.hpp"
#include "CustomVector.hpp"
#include "Exceptions.hpp"

#define TAB_STR "  "

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
    console.write("Failure at: ", console.setOpt(Console::ForgroundColor::Red), file, console.setOpt(Console::ForgroundColor::Yellow),'(', line, ')', '\n');
    for (const auto& desc : gTestDescStack) {
      for (int i = 0; i < tabcount; i++) {
	console.write(TAB_STR);
      }
      console.write(desc, '\n');
      tabcount++;
    }
    console.write('\n');
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
