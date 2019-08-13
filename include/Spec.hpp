#pragma once
#include <iostream>
#include <functional>
#include <exception>
#include <sstream>
#include <queue>
#include <vector>
#include <stdio.h>

#include "Expectation.hpp"

#define Begin(test_name)			\
  int func_##test_name();			\
  int var_##test_name = func_##test_name();	\
  int func_##test_name() {

#define End()	\
    return 0;	\
  }

void Describe(const char* desc, std::function<void(void)> func);
void Context(const char* context, std::function<void(void)> func);
void It(const char* test, std::function<void(void)> func);

class Spec {
  public:
    static void RunTests();

  private:
    static std::queue<std::function<void(void)>> mTests;
};
