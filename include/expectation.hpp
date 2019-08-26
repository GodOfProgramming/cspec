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
      console.write('\n', "In base", '\n');
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

  template <typename E>
  class Expectation<E, ExpectationOverride::CharChild> : public Expectation<char*, ExpectationOverride::CharBase> {
   public:
    Expectation(E value) : Expectation<char*, ExpectationOverride::CharBase>(value) {
      console.write('\n', "In CharChild", '\n');
    }

    void toEqual(char* value) {
      console.write('\n', "In CharChild toEqual", '\n');
      Expectation<E, ExpectationOverride::CharChild>::toEqual(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected '",
          mExpectation,
          "' to equal '",
          value,
          '\'',
          '\n',
          '\n');
    }

    template <typename... Args>
    void toEqual(char* value, Args&&... args) {
      if (strcmp(mExpectation, value)) {
        gItFailed = true;
        console.write(args...);
      }
    }
  };

  template <typename E>
  class Expectation<E, ExpectationOverride::ConstCharChild>
      : public Expectation<const char*, ExpectationOverride::ConstCharBase> {
   public:
    Expectation(E expectation) : Expectation<const char*, ExpectationOverride::ConstCharBase>(expectation) {
      console.write('\n', "In ConstCharChild", '\n');
    }

    void toEqual(const char* value) {
      console.write('\n', "In ConstCharChild toEqual", '\n');
      Expectation<E, ExpectationOverride::ConstCharChild>::toEqual(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected '",
          mExpectation,
          "' to equal '",
          value,
          '\'',
          '\n',
          '\n');
    }

    template <typename... Args>
    void toEqual(const char* value, Args&&... args) {
      if (strcmp(mExpectation, value)) {
        gItFailed = true;
        console.write(args...);
      }
    }
  };
}  // namespace cspec
