#pragma once
#include <iomanip>
#include "console.hpp"
#include "Exceptions.hpp"

extern bool gInItBlock;
extern bool gItFailed;

template <typename T>
class Expectation {
  public:
    Expectation(T expectation) : mExpectation(expectation) {}

    template <typename U>
    void toEqual(U value) {
      toEqual(value, 
	  "Expectation Failed -> ", "Expected: ", mExpectation, ",\n",
	  "                      ", "Got:      ", value, '\n');
    }

    template <typename U, typename... Args>
    void toEqual(U value, Args&& ...args) {
      if (mExpectation != value) {
	(console.write(std::forward<Args>(args)), ...);
	gItFailed = true;
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

