#pragma once
#include <iomanip>
#include "console.hpp"
#include "exceptions.hpp"

#define Expect(expectation) cspec::_Expect_(expectation)

namespace cspec {
extern bool gInItBlock;
extern bool gItFailed;

template <typename E>
class Expectation {
 public:
  Expectation(E expectation) : mExpectation(expectation) {}

  template <typename V>
  void toEqual(V value) {
    toEqual(value, console.setOpt<Console::Mod::FG_Cyan>(),
            "\nExpectation Failed\n  ",
            console.setOpt<Console::Mod::FG_Reset>(), "Expected ", mExpectation,
            " to equal ", value, '\n', '\n');
  }

  template <typename V, typename... Args>
  void toEqual(V value, Args&&... args) {
    if (mExpectation != value) {
      console.write(args...);
      gItFailed = true;
    }
  }

  template <typename V>
  void notToEqual(V value) {
    notToEqual(value, console.setOpt<Console::Mod::FG_Cyan>(),
               "\nExpectation Failed\n  ",
               console.setOpt<Console::Mod::FG_Reset>(), "Expected ",
               mExpectation, " not to equal ", value, '\n', '\n');
  }

  template <typename V, typename... Args>
  void notToEqual(V value, Args&&... args) {
    if (mExpectation == value) {
      console.write(args...);
      gItFailed = true;
    }
  }

  /* There are many kinds of iterables,
   * a for loop lets the usual (vector, map, etc...) work
   * along with anything else that defines the correct
   * functions (begin(), end())
   *
   * Also the programmer is required to supply a error message
   * since outputting a vector/unordered_map/etc... is not a standard
   * thing at this time
   */
  template <typename V, typename... Args>
  void toContain(V value, Args&&... args) {
    for (auto& element : mExpectation) {
      if (element == value) {
        return;
      }
    }

    gItFailed = true;
  }

  template <typename V, typename... Args>
  void notToContain(V value, Args&&... args) {
    for (auto& element : mExpectation) {
      if (element == value) {
        gItFailed = true;
      }
    }
  }

 private:
  E mExpectation;
};

template <typename T>
Expectation<T> _Expect_(T expectation) {
  if (!gInItBlock) {
    throw InvalidExpectationException();
  }
  return Expectation<T>(expectation);
}
}
