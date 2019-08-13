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

#define Describe(desc, func) _Describe_(desc, func)
#define Context(context, func) _Context_(context, func)
#define It(test, func) _It_(test, func, __FILE__, __LINE__)

void _Describe_(const char* desc, std::function<void(void)> func);
void _Context_(const char* context, std::function<void(void)> func);
void _It_(const char* test, std::function<void(void)> func, const char* file, int line);

class Spec {
  public:
    static void RunTests();

  private:
    static std::queue<std::function<void(void)>> mTests;
};


