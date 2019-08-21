#include <iostream>
#include <exception>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "console.hpp"
#include "spec.hpp"
#include "expectation.hpp"
#include "custom_vector.hpp"
#include "exceptions.hpp"

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
    console.write("Expectations can only be executed within it blocks", '\n');
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
  gTestDescStack.pop();
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
    console.write(
	"Failure at: ", 
	console.setOpt<Console::Mod::FG_Red>(), file, 
	console.setOpt<Console::Mod::FG_Yellow>(), '(', line, ')', '\n'
      );
    for (const auto& desc : gTestDescStack) {
      for (int i = 0; i < tabcount; i++) {
	console.write(TAB_STR);
      }
      console.write(desc, '\n');
      tabcount++;
    }
    console.write('\n');
  }

  gTestDescStack.pop();
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
