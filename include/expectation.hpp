#pragma once
#include <iomanip>
#include "console.hpp"
#include "string.h"

namespace cspec {
  extern bool gInItBlock;
  extern bool gItFailed;

  enum class ExpectationOverride { None, CharBase, CharChild, ConstCharBase, ConstCharChild };

  template <typename E, ExpectationOverride O>
  class Expectation {
   public:
    Expectation(E expectation) : mExpectation(expectation) {
    }

    template <typename V>
    void toEqual(V value) {
      console.write('\n', "In base toEqual", '\n');
      toEqual(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected ",
          mExpectation,
          " to equal ",
          value,
          '\n',
          '\n');
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
      notToEqual(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected ",
          mExpectation,
          " not to equal ",
          value,
          '\n',
          '\n');
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
     */
    template <typename V>
    void toContain(V value) {
      toContain(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected a container to contain ",
          value,
          '\n',
          '\n');
    }

    template <typename V, typename... Args>
    void toContain(V value, Args&&... args) {
      for (auto& element : mExpectation) {
        if (element == value) {
          return;
        }
      }

      gItFailed = true;
      console.write(args...);
    }

    template <typename V>
    void notToContain(V value) {
      notToContain(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected a container not to contain ",
          value,
          '\n',
          '\n');
    }

    template <typename V, typename... Args>
    void notToContain(V value, Args&&... args) {
      for (auto& element : mExpectation) {
        if (element == value) {
          gItFailed = true;
          console.write(args...);
          return;
        }
      }
    }

   protected:
    E mExpectation;
  };  // namespace cspec
}  // namespace cspec
