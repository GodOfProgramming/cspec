#pragma once
#include <iostream>
#include <functional>
#include <exception>
#include <sstream>
#include <queue>
#include <vector>
#include <stdio.h>

#define BeginTest(TestName) const auto TestName = []() -> int { \
  printf("%s:(%d)\n", __FILE__, __LINE__); fflush(stdout);

#define EndTest() return 0; }();

extern bool gInItBlock;

class SpecFailureException { public: SpecFailureException() = default; };
class InvalidExpectationException { public: InvalidExpectationException() = default; };

template <typename T>
class Expectation {
  public:
    Expectation(T expectation) : mExpectation(expectation) {}

    template <typename U>
    void toEqual(U value) {
      toEqual(value, "Expectation Failed:\n\tExpected: ", mExpectation, ",\n\tGot: ", value, '\n');
    }

    template <typename U, typename... Args>
    void toEqual(U value, Args&& ...args) {
      if (mExpectation != value) {
        ((std::cout << std::forward<Args>(args)), ...);
	throw SpecFailureException();
      }
    }

  private:
    T mExpectation;
};

template <typename T>
Expectation<T> Expect(T expectation) {
  if (!gInItBlock) {
    throw InvalidExpectationException();
  }
  return Expectation<T>(expectation);
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
