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
#include "describe_block.hpp"
#include "context_block.hpp"
#include "it_block.hpp"

#define TAB_STR "  "

namespace cspec {
  static CustomVector<TestBlock*> gTests;

  bool gInItBlock = false;
  bool gItFailed = false;

  unsigned int gSpecCount = 0;
  unsigned int gFailures = 0;

  TestBlock* gCurrentTest = nullptr;

  void RunTest(TestBlock& test) {
    try {
      test.run();
    } catch (InvalidExpectationException e) {
      console.write("Expectations can only be executed within it blocks", '\n');
    }
  }

  void _Describe_(const char* desc, TestFunc func) {
    auto prev_test = gCurrentTest;
    DescribeBlock db(desc, func);
    gCurrentTest = &db;
    gTests.push(gCurrentTest);
    RunTest(db);
    gTests.pop();
    gCurrentTest = prev_test;
  }

  void _Context_(const char* context, TestFunc func) {
    auto prev_test = gCurrentTest;
    ContextBlock cb(context, func);
    gCurrentTest = &cb;
    gTests.push(gCurrentTest);
    RunTest(cb);
    gTests.pop();
    gCurrentTest = prev_test;
  }

  void _It_(const char* test, TestFunc func, const char* file, int line) {
    auto prev_test = gCurrentTest;
    ItBlock ib(test, func);
    ib.PrevTests = gTests;
    gCurrentTest = &ib;
    gTests.push(gCurrentTest);

    gInItBlock = true;
    RunTest(ib);
    gInItBlock = false;

    gSpecCount++;

    if (gItFailed) {
      gFailures++;
      gItFailed = false;
      console.write(
	"Failure at: ", 
	console.setOpt<Console::Mod::FG_Red>(), file, 
	console.setOpt<Console::Mod::FG_Yellow>(), '(', line, ')', '\n'
      );
      printCurrentTestStack();
    } else {
      console.write(console.setOpt<Console::Mod::FG_Green>(), "\u2022");
    }

    gTests.pop();
    gCurrentTest = prev_test;
  }

  void _BeforeEach_(TestFunc func) {
    if (gCurrentTest) {
      gCurrentTest->beforeEach = func;
    }
  }

  void _AfterEach_(TestFunc func) {
    if (gCurrentTest) {
      gCurrentTest->afterEach = func;
    }
  }

  void printCurrentTestStack() {
    int tabcount = 1;
    for (const auto& test : gTests) {
      for (int i = 0; i < tabcount; i++) { 
	console.write(TAB_STR); 
      }
      console.write(test->Desc, '\n');
      tabcount++;
    }
  }
}

int main() {
  return !cspec::gFailures ? 0 : 1;
}
