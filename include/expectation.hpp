#pragma once
#include <console.hpp>
#include "matchers.hpp"
#include "string.h"

extern dash::Console console;

namespace cspec {
  extern bool gInItBlock;
  extern bool gItFailed;

  /* Can also be specialized if needed and won't break anything as long as you follow similar logic */
  template <typename E>
  class Expectation {
   public:
    Expectation(E expectation) : mExpectation(expectation) {
    }

    virtual ~Expectation() = default;

    template <typename V, typename... Args>
    void toEqual(V value, Args&&... args) {
      matchers::ToEqual<E, V> matcher;

      checkResult(matcher(mExpectation, value),
          console.setOpt<dash::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<dash::Mod::FG_Reset>(),
          matcher.Message,
          '\n',
          '\n',
          args...);
    }

    template <typename V>
    void notToEqual(V value) {
      notToEqual(value,
          console.setOpt<dash::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<dash::Mod::FG_Reset>(),
          "Expected ",
          mExpectation,
          " not to equal ",
          value,
          '\n',
          '\n');
    }

    template <typename V, typename... Args>
    void notToEqual(V value, Args&&... args) {
      matchers::NotToEqual<E, V> matcher;
      checkResult(matcher(mExpectation, value), args...);
    }

    template <typename V>
    void toContain(V value) {
      toContain(value,
          console.setOpt<dash::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<dash::Mod::FG_Reset>(),
          "Expected a container to contain ",
          value,
          '\n',
          '\n');
    }

    template <typename V, typename... Args>
    void toContain(V value, Args&&... args) {
      matchers::ToContain<E, V> matcher;

      checkResult(matcher(mExpectation, value), args...);
    }

    template <typename V>
    void notToContain(V value) {
      notToContain(value,
          console.setOpt<dash::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<dash::Mod::FG_Reset>(),
          "Expected a container not to contain ",
          value,
          '\n',
          '\n');
    }

    template <typename V, typename... Args>
    void notToContain(V value, Args&&... args) {
      matchers::NotToContain<E, V> matcher;
      checkResult(matcher(mExpectation, value), args...);
    }

   private:
    E mExpectation;

    template <typename... Args>
    void checkResult(bool res, Args&&... args) {
      if (!res) {
        console.write(args...);
        gItFailed = true;
      }
    }
  };
}  // namespace cspec
