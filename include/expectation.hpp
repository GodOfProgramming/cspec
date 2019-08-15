#pragma once
#include <iomanip>
#include "console.hpp"
#include "exceptions.hpp"

extern bool gInItBlock;
extern bool gItFailed;

template <typename E>
class Expectation {
  public:
    Expectation(E expectation) : mExpectation(expectation) {}

    template <typename V>
    void toEqual(V value) {
      toEqual(value, 
	"Expectation Failed\n  ", 
	"Expected ", 
	mExpectation, 
	" to equal ", 
	value, '\n', '\n'
      );
    }

    template <typename V, typename... Args>
    void toEqual(V value, Args&& ...args) {
      if (mExpectation != value) {
	(console.write(std::forward<Args>(args)), ...);
	gItFailed = true;
      }
    }

  private:
    E mExpectation;
};

template <typename T>
Expectation<T> Expect(T expectation) {
  if (!gInItBlock) {
    throw InvalidExpectationException();
  }
  return Expectation<T>(expectation);
}

