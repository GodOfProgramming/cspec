#pragma once
#include "matchers.hpp"
#include "console.hpp"
#include "string.h"

namespace cspec {
  extern bool gInItBlock;
  extern bool gItFailed;

  template <typename E>
  class Expectation {
   public:
    Expectation(E expectation) : mExpectation(expectation) {
    }

    virtual ~Expectation() = default;

    template <typename V>
    void toEqual(V value) {
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
      ToEqual<V> matcher(mExpectation);

      checkResult(matcher(value));
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
      NotToEqual<V> matcher(mExpectation);

      checkResult(matcher(value));
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
      ToContain<V> matcher(mExpectation);

      checkResult(matcher(value));
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
      notToContain<V> matcher(mExpectation);

      checkResult(matcher(value));
    }

   private:
    E mExpectation;

    template <typename... Args>
    inline void checkResult(bool res, Args&&... args) {
      if (!res) {
        console.write(args...);
        gItFailed = true;
      }
    }
  };
}  // namespace cspec
