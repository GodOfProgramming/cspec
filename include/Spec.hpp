#pragma once
#include <iostream>
#include <functional>
#include <exception>
#include <sstream>
#include <queue>
#include <vector>
#include <stdio.h>

#include "Expectation.hpp"

#define BeginTest(TestName) const auto TestName = []() -> int { \
  printf("%s:(%d)\n", __FILE__, __LINE__); fflush(stdout);

#define EndTest() return 0; }();

void Describe(const char* desc, std::function<void(void)> func);
void Context(const char* context, std::function<void(void)> func);
void It(const char* test, std::function<void(void)> func);

class Spec {
  public:
    static void RunTests();

  private:
    static std::queue<std::function<void(void)>> mTests;
};
