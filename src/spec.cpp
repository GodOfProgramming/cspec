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
  bool gAllPassed = true;

  TestBlock* gCurrentTest = nullptr;

  void RunTest(TestBlock& test) {
    try {
      test.run();
    } catch (InvalidExpectationException e) {
      console.write("Expectations can only be executed within it blocks", '\n');
      gAllPassed = false;
    }
  }

  void _Describe_(const char* desc, TestFunc func) {
    DescribeBlock db(desc, func);
    gCurrentTest = &db;
    gTests.push(gCurrentTest);
    RunTest(db);
    gTests.pop();
    gCurrentTest = nullptr;
  }

  void _Context_(const char* context, TestFunc func) {
    ContextBlock cb(context, func);
    gCurrentTest = &cb;
    gTests.push(gCurrentTest);
    RunTest(cb);
    gTests.pop();
    gCurrentTest = nullptr;
  }

  void _It_(const char* test, TestFunc func, const char* file, int line) {
    gInItBlock = true;
    ItBlock ib(test, func);
    ib.PrevTests = gTests;
    gCurrentTest = &ib;
    gTests.push(gCurrentTest);
    RunTest(ib);
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
      for (const auto& test : gTests) {
	for (int i = 0; i < tabcount; i++) {
	  console.write(TAB_STR);
	}
	console.write(test->Desc, '\n');
	tabcount++;
      }
      console.write('\n');
    }

    gTests.pop();
  }

  void _BeforeEach_(TestFunc func) {
    if (gCurrentTest) {
      gCurrentTest->beforeEach = func;
    }
  }
}

int main() {
  return cspec::gAllPassed ? 0 : 1;
}
